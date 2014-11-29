var currentTeamInModification = null;
function loadTeamModificationData()
{
	if(document.getElementById("team_number").value.length == 0)
	{
		openMessageBox("Incomplete Form!", "Please enter a valid team number!");
	}
	else
	{
		currentTeamInModification = document.getElementById("team_number").value;
		document.getElementById("team_number_display").innerHTML = "Team: " + document.getElementById("team_number").value;
		var tmp = "team=" + encodeURI(document.getElementById("team_number").value) + "&path=&name=name";
		AJAX_POST("/getvalue", tmp, function(x)
		{
			document.getElementById("team_name_mod").value = x;
		}, function(x) {});
		tmp = "team=" + encodeURI(document.getElementById("team_number").value) + "&path=&name=description";
		AJAX_POST("/getvalue", tmp, function(x)
		{
			document.getElementById("team_description_mod").value = x;
		}, function(x) {});
		tmp = "team=" + encodeURI(document.getElementById("team_number").value) + "&path=&name=school";
		AJAX_POST("/getvalue", tmp, function(x)
		{
			document.getElementById("team_school_mod").value = x;
		}, function(x) {});
		tmp = "team=" + encodeURI(document.getElementById("team_number").value) + "&path=&name=robot_description";
		AJAX_POST("/getvalue", tmp, function(x)
		{
			document.getElementById("robot_description_mod").value = x;
		}, function(x) {});
		tmp = "team=" + encodeURI(document.getElementById("team_number").value) + "&path=&name=drivetrain";
		AJAX_POST("/getvalue", tmp, function(x)
		{
			document.getElementById("robot_drivetrain_mod").value = x;
		}, function(x) {});
	}
}

function setTeamModificationData()
{
	var tmp = "team=" + encodeURI(currentTeamInModification) + "&path=&name=description&data=" + encodeURI(document.getElementById("team_description_mod").value);
	AJAX_POST("/setvalue", tmp, function(x) {}, function(x) {});
	var tmp = "team=" + encodeURI(currentTeamInModification) + "&path=&name=name&data=" + encodeURI(document.getElementById("team_name_mod").value);
	AJAX_POST("/setvalue", tmp, function(x) {}, function(x) {});
	var tmp = "team=" + encodeURI(currentTeamInModification) + "&path=&name=/school&data=" + encodeURI(document.getElementById("team_school_mod").value);
	AJAX_POST("/setvalue", tmp, function(x) {}, function(x) {});
	var tmp = "team=" + encodeURI(currentTeamInModification) + "&path=&name=robot_description&data=" + encodeURI(document.getElementById("robot_description_mod").value);
	AJAX_POST("/setvalue", tmp, function(x) {}, function(x) {});
	var tmp = "team=" + encodeURI(currentTeamInModification) + "&path=&name=drivetrain&data=" + encodeURI(document.getElementById("robot_drivetrain_mod").value);
	AJAX_POST("/setvalue", tmp, function(x) {}, function(x) {});
	openMessageBox("Team Modification Successful!", "The team data was modified sucessfully!");
	var tstamp = new Date().getMilliseconds();
	var tmp = "team=" + encodeURI(currentTeamInModification) + "&path=teammoddat&name=timestamp&data=" + encodeURI(tstamp);
	AJAX_POST("/setvalue", tmp, function(x){}, function(x){});

	loadTeamModificationData();

	handle_0000_refreshTeamModificationData = setInterval(refreshTeamModificationData, 1000);
}

var handle_0000_refreshTeamModificationData = null;
function refreshTeamModificationData()
{
	loadTeamModificationData();
	clearInterval(handle_0000_refreshTeamModificationData);
}