function boot_navigator()
{
	document.getElementById("nav-home").onclick = function()
	{
		changeBody("/file/html?loc=assets/web/html/home.mdhtml");
	}

	document.getElementById("apps-link").onclick = function()
	{
		openAppsPage();
	}

	document.getElementById("nav-home-apps").onclick = function()
	{
		changeBody("/file/html?loc=assets/web/html/home.mdhtml");
		closeAppsPage();
	};

	document.getElementById("nav-help-apps").onclick = function()
	{
		window.open("http://devyashis.me/wp/uberscout-help-and-faq", "_blank");
		closeAppsPage();
	};

	document.getElementById("team-registrar").onclick = function()
	{
		changeBody("/file/html?loc=assets/web/html/apps/team_registration.mdhtml");
		closeAppsPage();
	};

	document.getElementById("team-modify").onclick = function()
	{
		changeBody("/file/html?loc=assets/web/html/apps/team_modification.mdhtml");
		closeAppsPage();
	}

	document.getElementById("team-list-apps").onclick = function()
	{
		changeBody("/file/html?loc=assets/web/html/team_list.mdhtml");
		closeAppsPage();
		for(var i = 0; i < 128; i++)
		{
			if(bodyAt == "/file/html?loc=assets/web/html/team_list.mdhtml")
			{
				getTeamListing();
				break;
			}
		}
	}
}

function openMessageBox(caption, text)
{
	document.getElementById("caption").innerHTML = caption;
	document.getElementById("message_con").innerHTML = text;
	document.getElementById("mesbox").style.transform = "none";
	document.getElementById("mesbox").style.WebkitTransform = "none";
	document.getElementById("mesbox").style.MsTransform = "none";
	document.getElementById("mesbox").style.MozTransform = "none";
	document.getElementById("mesbox").style.OTransform = "none";
}

function closeMessageBox()
{
	document.getElementById("mesbox").style.transform = "translate(-150%, -150%) rotate(360deg)";
	document.getElementById("mesbox").style.WebkitTransform = "translate(-150%, -150%) rotate(360deg)";
	document.getElementById("mesbox").style.MsTransform = "translate(-150%, -150%) rotate(360deg)";
	document.getElementById("mesbox").style.MozTransform = "translate(-150%, -150%) rotate(360deg)";
	document.getElementById("mesbox").style.OTransform = "translate(-150%, -150%) rotate(360deg)";	
}