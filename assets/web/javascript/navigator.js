function boot_navigator()
{
	document.getElementById("nav-home").onclick = function()
	{
		changeBody("/file/html?loc=assets/web/html/home.mdhtml");
	}

	document.getElementById("nav-help").onclick = function()
	{
		window.open("http://devyashis.me/wp/uberscout-help-and-faq", "_blank");
	}

	document.getElementById("team-list").onclick = function()
	{
		changeBody("/file/html?loc=assets/web/html/team_list.mdhtml");
		if(bodyAt == "/file/html?loc=assets/web/html/team_list.mdhtml");
		{
			getTeamListing();
		}
	}
}
