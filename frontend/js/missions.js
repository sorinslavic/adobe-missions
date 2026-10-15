// Every mission shown in the vault: what it's called, what to do, and hints.
//
// hints: shown one at a time, in order
//
// tools: which tools appear next to the mission
//   "asset-request"     the brand asset request form
//   "brand-check"       live check for the button color
//   "department-check"  live check for the department field
//   "shop"              the Adobe Stock shop

export const MISSIONS = [
  {
    id: 0,
    title: "Boot log",
    topic: "Terminal",
    tags: ["Terminal"],
    difficulty: 1,
    brief: "When the vault booted, it said more than \"ready\". Go back to the terminal and read everything it printed.",
    hints: ["The vault talks the most when it wakes up."],
    tools: [],
    colors: { background: "#dff3e4", ink: "#123524", accent: "#1aa365" },
  },
  {
    id: 1,
    title: "Scrambled",
    topic: "Encodings",
    tags: ["Encodings"],
    difficulty: 1,
    brief: "To get familiar with the platform, here is a flag. It's scrambled: <code>bnFvcntjdTBnMGZ1MGNfY2UwfQ==</code> Unscramble it and paste it below. That's how every mission works.",
    hints: ["Those two equals signs at the end are a fingerprint. And if the result still looks odd, an old Roman would know what to do."],
    tools: [],
    colors: { background: "#ffe1d6", ink: "#3a1d14", accent: "#ff5c35" },
  },
  {
    id: 2,
    title: "Patient zero",
    topic: "Git history",
    tags: ["Git"],
    difficulty: 1,
    brief: "Every repository remembers who started it. The username of the very first author is the password.",
    hints: ["Git never forgets who did what, or when."],
    tools: [],
    colors: { background: "#e3e1ff", ink: "#211c55", accent: "#5b5bd6" },
  },
  {
    id: 3,
    title: "Between the lines",
    topic: "HTML",
    tags: ["HTML", "DevTools"],
    difficulty: 1,
    brief: "This page is carrying something it never shows on screen.",
    hints: ["What you see isn't everything your browser received."],
    tools: [],
    colors: { background: "#fff1bf", ink: "#3b2f05", accent: "#e59b00" },
  },
  {
    id: 4,
    title: "Slow down, agent",
    topic: "HTTP",
    tags: ["HTTP", "DevTools"],
    difficulty: 2,
    brief: "Send asset requests faster than the vault allows. When it tells you to stop, look closely at <em>how</em> it says it.",
    hints: ["A reply can say more than its message. Your browser's developer tools are listening."],
    tools: ["asset-request"],
    colors: { background: "#d8efff", ink: "#0b2d4a", accent: "#1d8fe0" },
  },
  {
    id: 5,
    title: "Brand compliance",
    topic: "CSS · JavaScript",
    tags: ["CSS", "JavaScript"],
    difficulty: 3,
    brief: "The <b>Send request</b> button must be Adobe Red <code>#EB1000</code>. Something keeps repainting it gray.",
    hints: ["Styles have a pecking order. And not everything that changes a page is a stylesheet."],
    tools: ["asset-request", "brand-check"],
    colors: { background: "#ffd9ea", ink: "#45102a", accent: "#eb1000" },
  },
  {
    id: 6,
    title: "New field, new tests",
    topic: "Forms · C++ · Tests",
    tags: ["HTML", "C++", "Tests"],
    difficulty: 3,
    brief: "The request form needs a <b>Department</b> field (Creative Cloud, Document Cloud, Experience Cloud). Add it, and get the vault to approve it.",
    hints: [
      "Every field starts its life in the page itself.",
      "The vault is picky about what it accepts.",
      "When the vault won't wake up, it usually says why. New features deserve proof.",
    ],
    tools: ["asset-request", "department-check"],
    colors: { background: "#e6f7d4", ink: "#1f3a0b", accent: "#5aa31a" },
  },
  {
    id: 7,
    title: "Negative balance",
    topic: "Input validation",
    tags: ["HTTP", "Logic"],
    difficulty: 2,
    brief: "The Vault Flag costs 1,000 credits. You have 100. Get it anyway.",
    hints: ["Shops count what you buy. Do they count carefully?"],
    tools: ["shop"],
    colors: { background: "#ffe8cc", ink: "#422405", accent: "#ff8a00" },
  },
];

export function findMission(missionId) {
  return MISSIONS.find((mission) => mission.id === missionId);
}
