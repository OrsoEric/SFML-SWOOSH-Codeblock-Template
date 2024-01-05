#pragma once

namespace Constant
{
	namespace Window
	{
		//Initial window size
		static const constexpr int cn_width = 800;
		static const constexpr int cn_height = 600;
	};


	static const constexpr char *cs_font = "resources/manual.ttf";

	static const constexpr char *cs_page_main_menu = "Page_main_menu";
	static const constexpr char *cs_page_village = "Page_village";

	namespace Simulation
	{
		static const constexpr float cf32_years_per_second = 0.25;

		static const constexpr float cn_land_rows = 10;
		static const constexpr float cn_land_cols = 10;
		static const constexpr float cn_land_total = cn_land_rows *cn_land_cols;
	};

	namespace Page_main_menu
	{
		static const constexpr char *cs_resource_background = "resources/black_rose_800_600.jpg";

	};

	namespace Page_village
	{
		static const constexpr char *cs_resource_background = "resources/parchment_800_600.jpg";
		static const constexpr char *cs_resource_tree = "resources/tree.jpg";
		static const constexpr char *cs_label_undeveloped = "Label_undeveloped";
	};

};
