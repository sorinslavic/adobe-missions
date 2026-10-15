// Live checks: ask the vault every few seconds whether a mission's requirements are met.

import { checkBrandColor, checkDepartmentReadiness } from "./api.js";

const CHECK_EVERY_MILLISECONDS = 2000;

let checkTimer = null;

function markCheck(elementId, isPassing) {
  document.getElementById(elementId).classList.toggle("is-passing", isPassing);
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

  markCheck("department-field-check", formHasDepartment);
  markCheck("department-stored-check", result.data.departmentStored === true);
  markCheck("department-test-check", result.data.departmentTestPassed === true);
  revealFlag("department-check-flag", formHasDepartment ? result.data.flag : null);
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
