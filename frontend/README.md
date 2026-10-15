# Frontend

The website of the vault. Plain HTML, CSS and JavaScript — no build step.
Change a file, refresh the browser, and you'll see the change.

## Files

| File | What it does |
| --- | --- |
| `index.html` | The page: the hub, the mission view, and the tools (request form, live checks, shop) |
| `css/app.css` | How everything looks |
| `css/brand.css` | Brand rules, loaded after `app.css` |
| `js/app.js` | Starts the website and decides what to show (`#m3` in the address bar opens mission 3) |
| `js/missions.js` | The list of missions: titles, descriptions and hints |
| `js/hub-view.js` | The hub with all mission tiles |
| `js/mission-view.js` | One mission: details, flag box and its tools |
| `js/mission-covers.js` | The small illustrations |
| `js/asset-request-form.js` | Sends the brand asset request form to the vault |
| `js/live-checks.js` | Asks the vault every few seconds whether a mission's requirements are met |
| `js/shop.js` | The Adobe Stock shop |
| `js/api.js` | Every call from the website to the backend |
| `js/brand-guard.js` | Keeps buttons in the brand colors |
| `fonts/`, `img/` | Adobe Clean font and the Adobe logo |
