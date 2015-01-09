var TeamScoutAndScore =
{
	LoadTeamData:function()
	{
		var tnum = document.getElementById("team_scout_score_team_number_input").value;
		if(!isNaN(tnum))
		{
			document.getElementById("dksjhkkhkfg_team_number").innerHTML = "Team " + document.getElementById("team_scout_score_team_number_input").value;
		}
	},
	OpenTeamDrawer:function()
	{
		askForTeam(function(x)
		{
			document.getElementById('team_scout_score_team_number_input').value = x;
			TeamScoutAndScore.LoadTeamData();
		});
	}
}