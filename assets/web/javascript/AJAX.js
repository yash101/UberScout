function AJAX_POST(location, data, callback, error)
{
	var xhr = new XMLHttpRequest();
	xhr.onreadystatechange = function()
	{
		if(xhr.readyState = 4)
		{
			callback(xhr.responseText);
		}
	};
	xhr.onerror = function()
	{
		var x = "The server failed to reply! Perhaps you may have lost connection to the server? Maybe the server was shutdown. Maybe there was some sort of fault that led to it's death!";
		x = x + "<div id=\"error_handler_func\" class=\"block\">Click here to retry request!</div>";
		openMessageBox("Displaying Error...", "Please wait while we load your error!");
		closeMessageBox();
		openMessageBox("Error loading content!", x);
		document.getElementById("error_handler_func").onclick = function()
		{
			AJAX_POST(location, data, callback, error);
		}
		error();
	};

	xhr.open("POST", location, true);
	xhr.setRequestHeader("Content-type","application/x-www-form-urlencoded");
	xhr.timeout = 4000;
	xhr.send(data);
}

function AJAX_GET(location, callback)
{
	var xhr = new XMLHttpRequest();
	xhr.onreadystatechange = function()
	{
		if(xhr.readyState == 4)
		{
			callback(xhr.responseText);
		}
	};

	xhr.onerror = function()
	{
		var g = "The server failed to reply! Perhaps you may have lost connection to the server? Maybe the server was shutdown. Maybe there was some sort of fault that led to it's death!";
		g = g + "<div id=\"error_handler_func\" class=\"block\">Click here to retry request!</div>";
		console.log(g);
		openMessageBox("Error loading content!", g);
		document.getElementById("error_handler_func").onclick = function()
		{
			AJAX_GET(location, callback);
		}
	};

	xhr.open("POST", location, true);
	xhr.timeout = 4000;
	xhr.send();
}