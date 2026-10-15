// The hub: shows every mission as a tile, with filters for open and solved missions.

import { MISSIONS } from "./missions.js";
import { drawMissionCover } from "./mission-covers.js";

let currentFilter = "all";
let lastSolvedMissionIds = new Set();

function difficultyDots(difficulty) {
  let dots = "";
  for (let level = 1; level <= 3; level++) {
    const filled = level <= difficulty ? "is-filled" : "";
    dots += `<span class="difficulty-dot ${filled}"></span>`;
  }
  return `<span class="difficulty-dots" title="Difficulty ${difficulty} of 3">${dots}</span>`;
}

function missionTile(mission, isSolved) {
  const badge = isSolved
    ? `<span class="tile-badge is-solved">✓ Solved</span>`
    : `<span class="tile-badge">Mission ${mission.id}</span>`;

  return `
    <button class="mission-tile" data-mission-id="${mission.id}">
      <span class="tile-cover">${drawMissionCover(mission)}${badge}</span>
      <span class="tile-caption">
        <span>
          <span class="tile-title">${mission.title}</span>
          <span class="tile-topic">${mission.topic}</span>
        </span>
        ${difficultyDots(mission.difficulty)}
      </span>
    </button>`;
}

function missionsMatchingFilter(solvedMissionIds) {
  if (currentFilter === "open") {
    return MISSIONS.filter((mission) => !solvedMissionIds.has(mission.id));
  }
  if (currentFilter === "solved") {
    return MISSIONS.filter((mission) => solvedMissionIds.has(mission.id));
  }
  return MISSIONS;
}

function drawTiles() {
  const tiles = missionsMatchingFilter(lastSolvedMissionIds)
    .map((mission) => missionTile(mission, lastSolvedMissionIds.has(mission.id)))
    .join("");
  document.getElementById("mission-tiles").innerHTML = tiles || `<p class="empty-message">Nothing here yet.</p>`;
}

function drawFilterButtons() {
  const openCount = MISSIONS.length - lastSolvedMissionIds.size;
  const labels = {
    all: `All ${MISSIONS.length}`,
    open: `Open ${openCount}`,
    solved: `Solved ${lastSolvedMissionIds.size}`,
  };
  for (const button of document.querySelectorAll(".filter-button")) {
    button.textContent = labels[button.dataset.filter];
    button.classList.toggle("is-active", button.dataset.filter === currentFilter);
  }
}

export function setupHub() {
  document.getElementById("filter-buttons").addEventListener("click", (event) => {
    const button = event.target.closest(".filter-button");
    if (button) {
      currentFilter = button.dataset.filter;
      drawFilterButtons();
      drawTiles();
    }
  });

  document.getElementById("mission-tiles").addEventListener("click", (event) => {
    const tile = event.target.closest(".mission-tile");
    if (tile) {
      location.hash = "m" + tile.dataset.missionId;
    }
  });
}

export function showHub(solvedMissionIds) {
  lastSolvedMissionIds = solvedMissionIds;
  drawFilterButtons();
  drawTiles();
  document.getElementById("hub-view").hidden = false;
}

export function hideHub() {
  document.getElementById("hub-view").hidden = true;
}
