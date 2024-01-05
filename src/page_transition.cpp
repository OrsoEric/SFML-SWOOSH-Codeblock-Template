//Pages shouldn't know about other pages
//Encapsulate page transition in a dedicated source

#include <iostream>

#include <Swoosh/ActivityController.h>
//#include <Swoosh/Segue.h>
#include <Segues/ZoomOut.h>

#include "constants.hpp"

#include "page_mainmenu.hpp"

#include "page_village.hpp"

extern bool page_push( swoosh::ActivityController& ircl_activity_controller, std::string is_page_name );
extern bool page_rewind( swoosh::ActivityController& ircl_activity_controller, std::string is_page_name );

bool page_push( swoosh::ActivityController& ircl_activity_controller, std::string is_page_name )
{
	using effect = swoosh::types::segue<ZoomOut, swoosh::types::sec<1>>;

	if (is_page_name == Constant::cs_page_main_menu)
	{
		ircl_activity_controller.push<effect::to<Page_mainmenu>>();
	}
	else if (is_page_name == Constant::cs_page_village)
	{
		ircl_activity_controller.push<effect::to<Page_village>>();
	}
	else
	{
		return true;
	}

	return false;
}

bool page_rewind( swoosh::ActivityController& ircl_activity_controller, std::string is_page_name )
{
	bool x_ret = false;

	using effect = swoosh::types::segue<ZoomOut, swoosh::types::sec<1>>;
	if (is_page_name == Constant::cs_page_main_menu)
	{
		x_ret |= ircl_activity_controller.rewind<effect::to<Page_mainmenu>>();
	}
	else if (is_page_name == Constant::cs_page_village)
	{
		x_ret |= ircl_activity_controller.rewind<effect::to<Page_village>>();
	}
	else
	{
		return true;
	}

	return x_ret;
}
