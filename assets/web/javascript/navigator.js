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
	};

	document.getElementById("team-list-apps").onclick = function()
	{
		changeBody("/file/html?loc=assets/web/html/team_list.mdhtml");
		closeAppsPage();
		getTeamListing();
	};

	document.getElementById("team-scout-scores-apps").onclick = function()
	{
		changeBody("/file/html?loc=assets/web/html/apps/team_scout_score.mdhtml");
		closeAppsPage();
	};

	document.getElementById("server-control-apps").onclick = function()
	{
		changeBody("/file/html?loc=assets/web/html/apps/ServerControl.mdhtml");
		closeAppsPage();
	};
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
	document.getElementById("mesbox").style.display = "block";
}

function closeMessageBox()
{
	document.getElementById("mesbox").style.transform = "translate(-150%, -150%) rotate(360deg)";
	document.getElementById("mesbox").style.WebkitTransform = "translate(-150%, -150%) rotate(360deg)";
	document.getElementById("mesbox").style.MsTransform = "translate(-150%, -150%) rotate(360deg)";
	document.getElementById("mesbox").style.MozTransform = "translate(-150%, -150%) rotate(360deg)";
	document.getElementById("mesbox").style.OTransform = "translate(-150%, -150%) rotate(360deg)";	
}

var team_picker_current_callback = null;
function askForTeam(callback)
{
	team_picker_current_callback = callback;
	var tbl_h = document.getElementById("team_picker");
	var tbl = document.getElementById("team_picker_table");

	tbl_h.style.top = "48px";
	tbl_h.style.left = "48px";
	tbl_h.style.right = "48px";
	tbl_h.style.bottom = "48px";

	AJAX_GET("/team_list?type=numbers", function(numbers)
	{
		AJAX_GET("/team_list?type=names", function(names)
		{
			console.log("Names: " + names);
			var team_numbers = numbers.split('\n');
			var team_names = names.split('\n');
			console.log("SNames: " + team_names);
			var o = "";
			o = o + "<tr>";
			o = o + "	<th>Team Number</th>";
			o = o + "	<th>Team Name</th>";
			o = o + "</tr>"
			for(var i = 0; i < team_numbers.length; i++)
			{
				if(team_numbers[i] != "")
				{
					o = o + "<tr onclick=\"javascript:returnTeamName('" + team_numbers[i] + "');\" class=\"TeamPickerRow\">";
					o = o + "	<td class=\"TeamPickerNumber\">" + team_numbers[i] + "</td>";
					o = o + "	<td class=\"TeamPickerName\">" + team_names[i] + "</td>";
					o = o + "</tr>";
				}
			}
			tbl.innerHTML = o;
		});
	});
}

function returnTeamName(num)
{
	team_picker_current_callback(num);
	closeTeamPicker();
}

function closeTeamPicker()
{
	var tbl = document.getElementById("team_picker");
	tbl.style.top = "-48px";
	tbl.style.left = "-48px";
	tbl.style.right = "1000%";
	tbl.style.bottom = "1000%";
}