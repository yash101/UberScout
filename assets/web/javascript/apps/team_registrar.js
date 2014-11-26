function submitTeamRegistrar()
{
	var tnumber = document.getElementById("team_registrar_number").value;
	var tname = document.getElementById("team_registrar_name").value;

	if(parseInt(tnumber) == 0 || parseInt(tnumber) == NaN || parseInt(tnumber) > 8000 || parseInt(tnumber) < 1)
	{
		openMessageBox("Team Addition Failure!", "Please enter an actual team number!");
	}

	if(tnumber.length == 0)
	{
		openMessageBox("Team Addition Failure!", "You did not enter a value for the team number!");
		return;
	}

	if(tname.length == 0)
	{
		openMessageBox("Team Addition Failure!", "You did not enter a value for the team name!");
		return;
	}

	openMessageBox("Team Addition Successful!", "The team was successfully added to the database!");

	var req = "team_number=" + encodeURI(tnumber) + "&team_name=" + encodeURI(tname);
	AJAX_POST("/team_list?type=add", req, function(x) {}, function(x) {});
}