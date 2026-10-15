// Small illustrations for each mission, drawn as SVG.

const ADOBE_LOGO_PATH = "M13.966 22.624l-1.69-4.281H8.122l3.892-9.144 5.662 13.425zM8.884 1.376H0v21.248zm15.116 0h-8.884L24 22.624Z";

function scrambledLettersArt({ ink, accent }) {
  return `
    <g font-family="ui-monospace, Menlo, monospace" font-weight="700" fill="${ink}">
      <text x="40" y="78" font-size="30" transform="rotate(-8 40 78)">YW</text>
      <text x="104" y="96" font-size="30" transform="rotate(6 104 96)">Ri</text>
      <text x="158" y="72" font-size="30" transform="rotate(-4 158 72)">ZX</text>
      <text x="214" y="98" font-size="30" transform="rotate(9 214 98)">sw</text>
      <text x="60" y="150" font-size="22" fill="${accent}">→ adbe{ ? }</text>
    </g>`;
}

function terminalArt({ background, ink, accent }) {
  return `
    <rect x="44" y="34" width="232" height="132" rx="10" fill="${ink}"/>
    <circle cx="62" cy="50" r="4" fill="${accent}"/>
    <g fill="${background}" opacity=".55">
      <rect x="60" y="70" width="120" height="7" rx="3"/>
      <rect x="60" y="86" width="160" height="7" rx="3"/>
      <rect x="60" y="134" width="90" height="7" rx="3"/>
    </g>
    <rect x="56" y="104" width="200" height="16" rx="4" fill="${accent}"/>
    <rect x="62" y="108" width="140" height="8" rx="3" fill="${background}"/>`;
}

function gitHistoryArt({ background, ink, accent }) {
  return `
    <path d="M90 30v140" stroke="${ink}" stroke-width="4"/>
    <g fill="${background}" stroke="${ink}" stroke-width="4">
      <circle cx="90" cy="46" r="9"/><circle cx="90" cy="78" r="9"/><circle cx="90" cy="110" r="9"/>
    </g>
    <circle cx="90" cy="158" r="16" fill="${accent}"/>
    <circle cx="90" cy="158" r="24" fill="none" stroke="${accent}" stroke-width="3" opacity=".4"/>
    <g fill="${ink}" opacity=".7">
      <rect x="124" y="152" width="110" height="8" rx="4"/>
      <rect x="124" y="104" width="80" height="6" rx="3" opacity=".5"/>
      <rect x="124" y="74" width="96" height="6" rx="3" opacity=".5"/>
    </g>`;
}

function htmlCommentArt({ ink, accent }) {
  return `
    <text x="160" y="114" text-anchor="middle" font-family="ui-monospace, Menlo, monospace" font-weight="700" font-size="40" fill="${ink}">
      &lt;!--<tspan fill="${accent}"> ? </tspan>--&gt;
    </text>`;
}

function tooManyRequestsArt({ ink, accent }) {
  return `
    <text x="160" y="128" text-anchor="middle" font-weight="900" font-size="88" fill="${ink}" letter-spacing="-4">429</text>
    <g stroke="${accent}" stroke-width="6" stroke-linecap="round">
      <path d="M28 74h40"/><path d="M18 100h50"/><path d="M34 126h34"/>
    </g>`;
}

function paintedButtonArt({ ink, accent }) {
  return `
    <rect x="70" y="80" width="180" height="48" rx="24" fill="#8e8e8e"/>
    <text x="160" y="111" text-anchor="middle" font-weight="700" font-size="18" fill="#ffffff">Send request</text>
    <path d="M210 40l40 40-20 20-40-40z" fill="${ink}"/>
    <path d="M228 100c0 10 6 16 6 24a6 6 0 01-12 0c0-8 6-14 6-24z" fill="${accent}"/>`;
}

function newFormFieldArt({ background, ink, accent }) {
  return `
    <rect x="80" y="26" width="160" height="148" rx="10" fill="${background}" stroke="${ink}" stroke-width="3"/>
    <g fill="${ink}" opacity=".7"><rect x="96" y="42" width="50" height="6" rx="3"/><rect x="96" y="80" width="50" height="6" rx="3"/></g>
    <g fill="none" stroke="${ink}" stroke-width="3" opacity=".7"><rect x="96" y="52" width="128" height="18" rx="4"/><rect x="96" y="90" width="128" height="18" rx="4"/></g>
    <rect x="96" y="122" width="128" height="34" rx="4" fill="none" stroke="${accent}" stroke-width="3" stroke-dasharray="6 5"/>
    <path d="M160 130v18M151 139h18" stroke="${accent}" stroke-width="4" stroke-linecap="round"/>`;
}

function priceTagArt({ background, ink, accent }) {
  return `
    <path d="M96 60h96l36 40-36 40H96z" fill="${ink}"/>
    <circle cx="110" cy="100" r="7" fill="${background}"/>
    <text x="168" y="113" text-anchor="middle" font-weight="900" font-size="38" fill="${background}">−10</text>
    <g fill="${accent}">
      <ellipse cx="250" cy="150" rx="22" ry="7"/><ellipse cx="250" cy="140" rx="22" ry="7"/><ellipse cx="250" cy="130" rx="22" ry="7"/>
    </g>`;
}

const ARTWORK_BY_MISSION = [
  scrambledLettersArt,
  terminalArt,
  gitHistoryArt,
  htmlCommentArt,
  tooManyRequestsArt,
  paintedButtonArt,
  newFormFieldArt,
  priceTagArt,
];

export function drawMissionCover(mission) {
  const drawArtwork = ARTWORK_BY_MISSION[mission.id];
  return `
    <svg viewBox="0 0 320 200" preserveAspectRatio="xMidYMid slice" role="img" aria-label="${mission.title}">
      <rect width="320" height="200" fill="${mission.colors.background}"/>
      ${drawArtwork(mission.colors)}
    </svg>`;
}

export function drawShopItemCover(itemId) {
  const covers = {
    "desert-sunrise": `<rect width="100" height="75" fill="#ffb347"/><circle cx="50" cy="52" r="15" fill="#ff6a3d"/><rect y="54" width="100" height="21" fill="#b5532a"/>`,
    "icon-pack": `<rect width="100" height="75" fill="#e5ebff"/><g fill="#3b63fb"><rect x="20" y="16" width="16" height="16" rx="4"/><circle cx="50" cy="24" r="8"/><path d="M64 32l8-16 8 16z"/><rect x="20" y="42" width="16" height="16" rx="8"/><rect x="42" y="42" width="16" height="16"/><path d="M72 42l8 8-8 8-8-8z"/></g>`,
    "font-license": `<rect width="100" height="75" fill="#131313"/><text x="50" y="49" text-anchor="middle" font-weight="900" font-size="28" fill="#ffffff">Aa</text>`,
    "vault-flag": `<rect width="100" height="75" fill="#eb1000"/><path transform="translate(38 25.5)" fill="#ffffff" d="${ADOBE_LOGO_PATH}"/>`,
  };
  return `<svg class="shop-item-cover" viewBox="0 0 100 75" preserveAspectRatio="xMidYMid slice" aria-hidden="true">${covers[itemId] || ""}</svg>`;
}
