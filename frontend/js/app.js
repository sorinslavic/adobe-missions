// Starts the website and decides what to show.
// The address bar decides: "#m3" opens mission 3, anything else shows the hub.

import { getProgress } from "./api.js";
import { setupAssetRequestForm } from "./asset-request-form.js";
import { hideHub, setupHub, showHub } from "./hub-view.js";
import { findMission, MISSIONS } from "./missions.js";
import { hideMission, showMission } from "./mission-view.js";
import { setupShop } from "./shop.js";

let solvedMissionIds = new Set();

function showProgressInTopBar() {
  document.getElementById("solved-count").textContent = solvedMissionIds.size;
  document.getElementById("progress-bar").innerHTML = MISSIONS.map((mission) => {
    const solved = solvedMissionIds.has(mission.id) ? "is-solved" : "";
    return `<span class="progress-step ${solved}"></span>`;
  }).join("");
}

async function loadProgress() {
  const result = await getProgress();
  solvedMissionIds = new Set(result.data.solved || []);
  showProgressInTopBar();
}

function missionIdFromAddressBar() {
  const match = location.hash.match(/^#m(\d+)$/);
  return match ? Number(match[1]) : null;
}

async function showCurrentPage() {
  await loadProgress();
  const mission = findMission(missionIdFromAddressBar());

  if (mission) {
    hideHub();
    showMission(mission, solvedMissionIds.has(mission.id), showCurrentPage);
  } else {
    hideMission();
    showHub(solvedMissionIds);
  }
}

setupHub();
setupAssetRequestForm();
setupShop();
window.addEventListener("hashchange", showCurrentPage);
showCurrentPage();
