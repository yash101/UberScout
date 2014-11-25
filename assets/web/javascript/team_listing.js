function team_listing_bootloader()
{
	getTeamListing();
}

var team_listing_tnumbers = null;


function getTeamListing()
{
	AJAX_GET("/team_list?type=numbers", function(x)
	{
		team_listing_tnumbers = x;
		AJAX_GET("/team_list?type=names", function(y)
		{
			var nums = team_listing_tnumbers.split('\n');
			var names = y.split('\n');
			var o = "";
			o = o + "<tr>";
			o = o + "	<th class=\"TeamNumber\">Team Number</th>";
			o = o + "	<th class=\"TeamName\">Team Name</th>";
			o = o + "</tr>";
			for(var i = 0; i < nums.length; i++)
			{
				if(nums[i] != "")
				{
					o = o + "<tr class=\"TeamListingHighlighterRow\">";
					o = o + "	<td class=\"TeamNumber\">" + nums[i] + "</td>";
					o = o + "	<td class=\"TeamName\">" + names[i] + "</td>";
					o = o + "</tr>";
				}
			}
			document.getElementById("main_tbl_team_list").innerHTML = o;
		});
	});
}