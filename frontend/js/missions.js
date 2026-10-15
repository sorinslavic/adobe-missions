// Every mission shown in the vault: what it's called, what to do, and a hint.
//
// tools: which tools appear next to the mission
//   "asset-request"     the brand asset request form
//   "brand-check"       live check for the button color
//   "department-check"  live check for the department field
//   "shop"              the Adobe Stock shop

export const MISSIONS = [
  {
    id: 0,
    title: "Scrambled",
    topic: "Encodings",
    tags: ["README", "Base64", "ROT13"],
    difficulty: 1,
    brief: "Your first flag is already in the README, but it's scrambled. Unscramble it and paste it below. That's how every mission works.",
    hint: "It looks like Base64. Still weird after decoding? Shift every letter by 13.",
    tools: [],
    colors: { background: "#ffe1d6", ink: "#3a1d14", accent: "#ff5c35" },
  },
  {
    id: 1,
    title: "Boot log",
    topic: "Terminal",
    tags: ["Terminal"],
    difficulty: 1,
    brief: "When the vault booted, it said more than \"ready\". Go back to the terminal and read everything it printed.",
    hint: "Scroll up in the terminal where the vault is running.",
    tools: [],
    colors: { background: "#dff3e4", ink: "#123524", accent: "#1aa365" },
  },
  {
    id: 2,
    title: "Patient zero",
    topic: "Git history",
    tags: ["Git"],
    difficulty: 1,
    brief: "Every repository remembers who started it. The username of the very first author is the password.",
    hint: "<code>git log</code> shows authors. Which commit is the oldest?",
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
    hint: "Browsers skip some parts of HTML. Try View Page Source.",
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
    hint: "A response is more than its body. DevTools → Network → click the failed request → Headers.",
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
    hint: "HTML loses to CSS. CSS loses to <code>!important</code>. What runs after CSS?",
    tools: ["asset-request", "brand-check"],
    colors: { background: "#ffd9ea", ink: "#45102a", accent: "#eb1000" },
  },
  {
    id: 6,
    title: "New field, new tests",
    topic: "Forms · C++ · Tests",
    tags: ["HTML", "C++", "Tests"],
    difficulty: 3,
    brief: "Add a <b>Department</b> field (Creative Cloud, Document Cloud, Experience Cloud) to the request form. The vault must store it, and a test must prove it.",
    hint: "If the vault refuses to start, read the terminal. A test is telling you what it expected.",
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
    hint: "What does the server do with a quantity nobody expected?",
    tools: ["shop"],
    colors: { background: "#ffe8cc", ink: "#422405", accent: "#ff8a00" },
  },
];

export function findMission(missionId) {
  return MISSIONS.find((mission) => mission.id === missionId);
}
