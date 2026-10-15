// Live checks: ask the vault every few seconds whether a mission's requirements are met.

import { checkBrandColor, checkDepartmentReadiness } from "./api.js";

const CHECK_EVERY_MILLISECONDS = 2000;

let checkTimer = null;

function markCheck(elementId, isPassing) {
  document.getElementById(elementId).classList.toggle("is-passing", isPassing);
}

// Only lists a requirement once it is met, so the list never gives away what comes next.
function showWhenMet(elementId, isMet) {
  document.getElementById(elementId).hidden = !isMet;
}

function revealFlag(elementId, flag) {
  const box = document.getElementById(elementId);
  if (!flag) {
    box.hidden = true;
    return;
  }
  box.innerHTML = "Approved! Your flag: <code></code>";
  box.querySelector("code").textContent = flag;
  box.hidden = false;
}

async function runBrandCheck() {
  const button = document.getElementById("send-request");
  const currentColor = getComputedStyle(button).backgroundColor;

  document.getElementById("current-color-swatch").style.background = currentColor;
  document.getElementById("current-color-value").textContent = currentColor;

  const result = await checkBrandColor(currentColor);
  markCheck("brand-color-check", result.data.approved === true);
  revealFlag("brand-check-flag", result.data.flag);
}

async function runDepartmentCheck() {
  const formHasDepartment = document.querySelector('#asset-request-form [name="department"]') !== null;
  const result = await checkDepartmentReadiness();

  const departmentAccepted = result.data.departmentAccepted === true;
  const departmentTestPassed = result.data.departmentTestPassed === true;
  const everythingMet = formHasDepartment && departmentAccepted && departmentTestPassed;

  showWhenMet("department-field-check", formHasDepartment);
  showWhenMet("department-accepted-check", departmentAccepted);
  showWhenMet("department-test-check", departmentTestPassed);
  document.getElementById("department-check-waiting").hidden = everythingMet;
  revealFlag("department-check-flag", everythingMet ? result.data.flag : null);
}

export function startLiveChecks(toolNames) {
  stopLiveChecks();

  const checks = [];
  if (toolNames.includes("brand-check")) {
    checks.push(runBrandCheck);
  }
  if (toolNames.includes("department-check")) {
    checks.push(runDepartmentCheck);
  }
  if (checks.length === 0) {
    return;
  }

  const runAllChecks = () => checks.forEach((check) => check());
  runAllChecks();
  checkTimer = setInterval(runAllChecks, CHECK_EVERY_MILLISECONDS);
}

export function stopLiveChecks() {
  clearInterval(checkTimer);
  checkTimer = null;
}
