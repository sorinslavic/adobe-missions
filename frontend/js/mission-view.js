// The mission view: details and flag box on the left, the mission's tools on the right.

import { submitFlag } from "./api.js";
import { drawMissionCover } from "./mission-covers.js";
import { startLiveChecks, stopLiveChecks } from "./live-checks.js";
import { loadShop } from "./shop.js";

const TOOL_ELEMENT_IDS = {
  "asset-request": "asset-request-tool",
  "brand-check": "brand-check-tool",
  "department-check": "department-check-tool",
  "shop": "shop-tool",
};

const FLAG_FORMAT = /^adbe\{.+\}$/;

function hintButtonLabel(mission, hintsShown) {
  if (mission.hints.length === 1) {
    return "Show hint";
  }
  const nextHint = hintsShown + 1;
  return hintsShown === 0
    ? `Show hint (1 of ${mission.hints.length})`
    : `Show next hint (${nextHint} of ${mission.hints.length})`;
}

// Reveals the hints one at a time, in order.
function setupHints(mission) {
  let hintsShown = 0;
  const list = document.getElementById("hint-list");
  const button = document.getElementById("hint-button");

  button.addEventListener("click", () => {
    const hint = document.createElement("li");
    hint.innerHTML = mission.hints[hintsShown];
    list.appendChild(hint);
    hintsShown++;

    if (hintsShown === mission.hints.length) {
      button.hidden = true;
    } else {
      button.textContent = hintButtonLabel(mission, hintsShown);
    }
  });
}

function missionPanel(mission, isSolved) {
  const tags = mission.tags.map((tag) => `<span class="mission-tag">${tag}</span>`).join("");


  const flagBox = isSolved
    ? `<div class="solved-banner">✓ Solved. Nice work, intern.</div>`
    : `
      <form class="flag-form" id="flag-form">
        <label for="flag-input" hidden>Flag</label>
        <input class="flag-input" id="flag-input" placeholder="adbe{...}" autocomplete="off" spellcheck="false">
        <button class="flag-submit" type="submit">Submit flag</button>
        <div class="flag-message" id="flag-message" aria-live="polite"></div>
      </form>`;

  return `
    <button class="back-button" id="back-button">← All missions</button>
    <div class="mission-cover">${drawMissionCover(mission)}</div>
    <h2 class="mission-title">${mission.title}</h2>
    <div class="mission-tags">${tags}</div>
    <p class="mission-brief">${mission.brief}</p>
    <div class="hints">
      <ol class="hint-list" id="hint-list"></ol>
      <button class="hint-button" id="hint-button" type="button">${hintButtonLabel(mission, 0)}</button>
    </div>
    ${flagBox}`;
}

function returnToolsToShelf() {
  const shelf = document.getElementById("tool-shelf");
  for (const elementId of Object.values(TOOL_ELEMENT_IDS)) {
    shelf.appendChild(document.getElementById(elementId));
  }
}

function placeToolsOnCanvas(mission) {
  const canvas = document.getElementById("mission-canvas");
  canvas.innerHTML = "";

  if (mission.tools.length === 0) {
    canvas.innerHTML = `<div class="canvas-cover">${drawMissionCover(mission)}</div>`;
    return;
  }
  for (const toolName of mission.tools) {
    canvas.appendChild(document.getElementById(TOOL_ELEMENT_IDS[toolName]));
  }
}

function setupFlagForm(mission, onMissionSolved) {
  const form = document.getElementById("flag-form");
  if (!form) {
    return;
  }

  form.addEventListener("submit", async (event) => {
    event.preventDefault();
    const flag = document.getElementById("flag-input").value.trim();
    const message = document.getElementById("flag-message");

    if (!FLAG_FORMAT.test(flag)) {
      message.className = "flag-message is-error";
      message.textContent = "Flags look like adbe{password}.";
      return;
    }

    const result = await submitFlag(mission.id, flag);
    if (result.data.correct) {
      onMissionSolved();
    } else {
      message.className = "flag-message is-error";
      message.textContent = "Not this one. Keep digging.";
    }
  });
}

export function showMission(mission, isSolved, onMissionSolved) {
  returnToolsToShelf();
  document.getElementById("mission-panel").innerHTML = missionPanel(mission, isSolved);
  document.getElementById("back-button").addEventListener("click", () => {
    location.hash = "";
  });
  setupHints(mission);
  setupFlagForm(mission, onMissionSolved);
  placeToolsOnCanvas(mission);

  if (mission.tools.includes("shop")) {
    loadShop();
  }
  startLiveChecks(mission.tools);

  document.getElementById("mission-view").hidden = false;
  window.scrollTo(0, 0);
}

export function hideMission() {
  stopLiveChecks();
  returnToolsToShelf();
  document.getElementById("mission-view").hidden = true;
}
