window.onload = function()
{
}

function openAppsPage()
{
	var appsPage = document.getElementById("applications_menu");
//	document.getElementById("applications_menu_disp").style.display = "block";
	appsPage.style.top = "64px";
	appsPage.style.left = "64px";
	appsPage.style.bottom = "64px";
	appsPage.style.right = "64px";
}

function closeAppsPage()
{
	var appsPage = document.getElementById("applications_menu");
	appsPage.style.top = "200%";
	appsPage.style.left = "-100%";
	appsPage.style.bottom = "-100%";
	appsPage.style.right = "100%";
	// clearInterval(appsPageRemoverCron);
	// appsPageRemoverCron = setInterval(removeAppsPage, 800);
}

// var appsPageRemoverCron = null;
// function removeAppsPage()
// {
// 	clearInterval(appsPageRemoverCron);
// 	document.getElementById("applications_menu_disp").style.display = "none";
// }