#include <iostream>

namespace Utils
{
	//in_zero is in point zero
	//in_one is in point one
	//in_point is the point where you are sampling
	float interpolate( float in_zero, float in_one, float in_point )
	{
		return in_zero + in_point * (in_one - in_zero);
	}


	void clip_inplace( float in_min, float &in_num, float in_max )
	{
		if (in_num <= in_min)
		{
			in_num = in_min;
			return;
		}
		else if (in_num >= in_max)
		{
			in_num = in_max;
			return;
		}
		return;
	}

}

class Village_simulator
{
public:
	//Encapsulates plots of land
	struct Land
	{
		//finite resource, all land not developed or wild is undeveloped
		float n_total = 0.0f;
		float n_undeveloped = 0.0f;
		float n_wood = 0.0f;
		//Plots developed as fields
		float n_field = 0.0f;
		//Plots developed as buildings
		float n_built = 0.0f;
		//Compute the total undeveloped land and check it's consistent
		bool compute_undeveloped()
		{
			//Total used land
			float n_developed = this->n_wood +this->n_field +this->n_built;
			//Developed land exceed total land
			if (n_developed > n_total)
			{
				return true;
			}
			this->n_undeveloped = this->n_total -n_developed;
			return false;
		}
		//Stringfy the structure
		std::string to_str()
		{
			return std::string("Land | Total: ") +std::to_string(this->n_total)
				   +" | Undeveloped: "+std::to_string(this->n_undeveloped)
				   +" | Woods: " +std::to_string(this->n_wood)
				   +" | Field: " +std::to_string(this->n_field)
				   +" | Built: " +std::to_string(this->n_built);
		}
	};

	//Extend the Land to incorporate the Land_system simulation
	struct Land_system : Land
	{
		//Wild Growth rate per year under the best environmental conditions
		float n_growth_rate_best = 0.07f;
		//Wild Growth rate per year under the worst environmental conditions
		float n_growth_rate_worst = 0.01f;
		//Environmental decay rate per year under the best environmental conditions
		float n_decay_rate_best = -0.01f;
		//Environmental decay rate per year under the worst environmental conditions
		float n_decay_rate_worst = -0.11f;
		//Overall bonus to be applied to the simulation. 0.1 means 10%. 1.0 means 100%. Bonus can be negative.
		float n_bonus = 0.0f;

		//Aid function to apply decay and growth
		bool apply_growth_decay( float &iorn_status_var, float in_rate_per_year, float in_years )
		{
			//Difference at the end of the elapsed time
			float n_difference =  iorn_status_var *in_rate_per_year *in_years;
			//Land can't be subtracted below zero or more additional land than undeveloped land
			Utils::clip_inplace( -iorn_status_var, n_difference, this->n_undeveloped );
			//Integrate
			iorn_status_var += n_difference;
			return false; //OK
		}

		//Simulate a number of years of growth/decay
		//in_environment | 0.0 = Worst environment | 1.0 best environment
		bool simulate( float in_years, float in_environment )
		{
			//Wild Growth and Decay
			float n_growth_per_year = Utils::interpolate( n_growth_rate_worst, n_growth_rate_best, in_environment ) *(1.0f +n_bonus);
			float n_decay_per_year = Utils::interpolate( n_decay_rate_worst, n_decay_rate_best, in_environment ) /(1.0f +n_bonus);
			//Woods have a natural growth to fight the natural decay. With net positive growth, they grow
			bool x_ret = apply_growth_decay( this->n_wood, n_growth_per_year +n_decay_per_year, in_years );
			//Fields decay into undeveloped land
			x_ret |= apply_growth_decay( this->n_field, n_decay_per_year, in_years );
			//Buildings decay into undeveloped land
			x_ret |= apply_growth_decay( this->n_built, n_decay_per_year, in_years );
			//Compute remaining undeveloped land
			x_ret |= this->compute_undeveloped();
			return x_ret;
		}
	};

	Village_simulator()
	{
		this->set_land( 0, 0, 0, 0 );
		return;
	}

	//Set the available land
	bool set_land( int in_total_plots, int in_wood, int in_field, int in_built )
	{
		this->gst_land.n_total = in_total_plots;
		this->gst_land.n_wood = in_wood;
		this->gst_land.n_field = in_field;
		this->gst_land.n_built = in_built;
		return this->gst_land.compute_undeveloped();
	}

	Land get_land()
	{
		return this->gst_land;
	}

	float &ref_land_bonus( void )
	{
		return this->gst_land.n_bonus;
	}

	//Run the simulation
	bool simulate( float in_years, float in_enviroment )
	{
		bool x_ret = false;
		x_ret |= this->gst_land.simulate( in_years, in_enviroment );
		return false;
	}


	std::string show_land()
	{
		return this->gst_land.to_str();
	}
private:



	//LAND SIMULATION
	Land_system gst_land;

};
