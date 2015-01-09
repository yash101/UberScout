window.onload = function()
{
}

function openAppsPage()
{
	var appsPage = document.getElementById("applications_menu");
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
}
