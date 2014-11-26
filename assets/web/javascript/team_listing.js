function team_listing_bootloader()
{
	getTeamListing();
}

function deleteTeam(number)
{
	AJAX_POST("/team_list?type=remove", "team=" + encodeURI(number), function(x)
	{
		//document.getElementById("content").innerHTML = "<h1>Successfully deleted team number " + number + "</h1>";
		openMessageBox("Team Deletion Output", "<h1>Successfully deleted team number " + number + "</h1>");
	}, function()
	{
		//document.getElementById("content").innerHTML = "<h1>Failed deleting team number " + number + "</h1>";		
		openMessageBox("Team Deletion Output", "<h1>Failed deleting team number " + number + "</h1>");
	});
}

function askDelete(number, name)
{
	var o = "<h1>Delete Team!</h1>";
	o = o + "<strong>Are you Sure that you would like to delete team " + number + ", a.k.a. " + name + "?</strong>";
	o = o + "<button onclick=\"javascript:deleteTeam(" + number + ");\" style=\"width: 100%; border: 4px solid #98BF21; height: 32px; font-size: 18px; background-color: #404040; color: #C6C6C6;\">Click Here to Delete!</button>";
//	document.getElementById("content").innerHTML = o;
	openMessageBox("Team Deletion Confirmation!", o);
}

function getTeamListing()
{
	var team_listing_tnumbers = null;
	AJAX_GET("/team_list?type=numbers", function(x)
	{
		team_listing_tnumbers = x;
		AJAX_GET("/team_list?type=names", function(y)
		{
			var nums = team_listing_tnumbers.split('\n');
			var names = y.split('\n');
			var o = "";
			o = o + "<tr>";
			o = o + "	<th class=\"DeleteBtn\">X</th>";
			o = o + "	<th class=\"TeamNumber\">Team Number</th>";
			o = o + "	<th class=\"TeamName\">Team Name</th>";
			o = o + "</tr>";
			for(var i = 0; i < nums.length; i++)
			{
				if(nums[i] != "")
				{
					o = o + "<tr class=\"TeamListingHighlighterRow\">";
					o = o + "<td class=\"DeleteBtn\" onclick=\"javascript:askDelete(" + nums[i] + ", '" + names[i] + "');\"\">X</td>";
					o = o + "	<td class=\"TeamNumber\">" + nums[i] + "</td>";
					o = o + "	<td class=\"TeamName\">" + names[i] + "</td>";
					o = o + "</tr>";
				}
			}
			document.getElementById("main_tbl_team_list").innerHTML = o;
		});
	});
}