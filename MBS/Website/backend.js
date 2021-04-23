// Florian Crafter 1.2

// 0 0000000000 0000000 00000 0000 0000
// p   config    count   id   prod. ver

const buyConfig = {
  count: 5,
  config: ["monitoringDisplay", "boxSizeSmall", "saveNo"]
};

const lengths = {
  ver: 4,
  prod: 4,
  id: 5,
  count: 7,
  config: 10,
  parity: 1,
};

const co2Config = {
  productId: 1,
  monitoringLed: {
    internPos: 0,
    internVal: 0,
    externNeeds: [],
    externDonts: ["monitoringDisplay"],
    description: "Um den CO2 Wert auszulesen nutzt man eine LED.",
    picture: "",
  },
  monitoringDisplay: {
    internPos: 0,
    internVal: 1,
    externNeeds: [],
    externDonts: ["monitoringLed"],    
    description: "Um den CO2 Wert auszulesen nutzt man ein LCD Display.",
    picture: "",
  },
  boxSizeSmall: { 
    internPos: 1, 
    internVal: 0, 
    externNeeds: [], 
    externDonts: ["boxSizeBig"],    
    description: "Nutze eine große Box.",
    picture: "",
  },
  boxSizeBig: { 
    internPos: 1, 
    internVal: 1, 
    externNeeds: [], 
    externDonts: ["boxSizeSmall"],
    description: "Nutze eine kleine Box.",
    picture: "",
    },
  saveNo: { 
    internPos: 3, 
    internVal: 0, 
    externNeeds: [], 
    externDonts: ["saveYes"],    
    description: "Speichere die Daten auf eine SD-Karte. SD-Karte NICHT inkludiert!",
    picture: "",
  },
  saveYes: { 
    internPos: 3, 
    internVal: 1, 
    externNeeds: [], 
    externDonts: ["saveNo"],    
    description: "Speichere nicht die Daten.",
    picture: "",
  },
  colorGray: {
    internPos: 4,
    internVal: 1,
    externNeeds: [],
    externDonts: ["colorWhite", "colorBlack"],
    description: "Habe eine graue Box.",
    picture: "",
  },
  colorWhite: {
    internPos: 5,
    internVal: 1,
    externNeeds: [],
    externDonts: ["colorGray", "colorBlack"],
    description: "Habe eine weiße Box.",
    picture: "",
  },
  colorBlack: {
    internPos: 6,
    internVal: 1,
    externNeeds: [],
    externDonts: ["colorGray", "colorWhite"],
    description: "Habe eine schwarze Box.",
    picture: "",
  },

};

function GenerateId() {
  return Math.floor(Math.random() * (Math.pow(2, lengths.id) + 1)); // generate random id
}

// @ts-ignore
function MeaningToNumber(productConfig, buyConfig, version) {
  let n = 0;

  // set version
  n = setBits(n, version);

  // set product number
  n = setBits(n, productConfig.productId << lengths.ver);

  // set id
  n = setBits(n, GenerateId() << (lengths.ver + lengths.prod));

  // set count
  n = setBits(n, buyConfig.count << (lengths.ver + lengths.prod + lengths.id));

  // set config
  let config = 0;
  for (let [key, value] of Object.entries(productConfig))
    if (buyConfig.config.includes(key))
      // @ts-ignore
      config = setBits(config, value.internVal << value.internPos); // get config data

  n = setBits(
    n,
    config << (lengths.ver + lengths.prod + lengths.id + lengths.count)
  );

  // set parity
  n = setBits(
    n,
    getParity(n) <<
      (lengths.ver +
        lengths.prod +
        lengths.id +
        lengths.count +
        lengths.config)
  );

  return n;
}

// @ts-ignore
function NumberToMeaning(productConfig, n) {
  let str = "";

  // get version
  str += "Code version: " + getBits(n, 0, lengths.ver);
  // remove version
  n = removeBits(n, 0, lengths.ver);

  // get product id
  str += ", Product id: " + getBits(n, 0, lengths.prod);
  // remove product id
  n = removeBits(n, 0, lengths.prod);

  // get ID
  str += ", Buy id: " + getBits(n, 0, lengths.id);
  // remove ID
  n = removeBits(n, 0, lengths.id);

  // get count
  str += ", Count: " + getBits(n, 0, lengths.count);
  // remove count
  n = removeBits(n, 0, lengths.count);

  // get config
  for (let [key, value] of Object.entries(productConfig))
    // @ts-ignore
    if (value.internPos !== undefined && getBit(n, value.internPos) == value.internVal) str += ", " + key;
  // remove config
  n = removeBits(n, 0, lengths.config);

  // get parity
  str +=
    ", Parity: " +
    getBits(
      n,
      0,
      lengths.parity
    );
  // remove parity
  n = clearBits(
    n,
    0,
    lengths.parity
  );

  return str;
}

// #region bit manipulation
// @ts-ignore
const setBits = (n, bits) => n | bits;

// @ts-ignore
const getBit = (n, pos) => (n & (1 << pos)) >> pos;

// @ts-ignore
const getBits = function (n, posStart, count) {
  let bits = 0;
  for (let i = posStart; i < posStart + count; ++i) bits |= getBit(n, i) << i;
  return bits >> posStart;
};

// @ts-ignore
const clearBit = (n, pos) => n & ~(1 << pos);

// @ts-ignore
const clearBits = function (n, posStart, count) {
  for (let i = posStart; i < posStart + count; ++i) n = clearBit(n, i);
  return n;
};

// @ts-ignore
const removeBits = (n, posStart, count) =>
  clearBits(n, posStart, count) >> count;

// @ts-ignore
const getParity = (n) => ((n.toString(2).split("1") ?? []).length - 1) & 1;
// #endregion

console.log("input:", buyConfig);
const output = MeaningToNumber(co2Config, buyConfig, 1);
console.log(
  output + " (" + output.toString(2) + ") => " + NumberToMeaning(co2Config, output)
);
