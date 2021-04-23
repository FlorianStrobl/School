// Florian Crafter 1.0

// 0 0000000000 0000000 00000 0000 0000
// p   config    count   id   prod. ver

let input = ["monitoringDisplay", "boxSizeSmall", "saveNo"];
let input2 = 5;

const version = 1;
const produktCo2 = 1;

const lengths = {
  ver: 4,
  prod: 4,
  id: 5,
  count: 7,
  congfig: 10,
  parity: 1,
};

const internal = {
  monitoringLed: {
    position: 0,
    value: 0,
    needs: [],
    donts: ["monitoringDisplay"],
  },
  monitoringDisplay: {
    position: 0,
    value: 1,
    needs: [],
    donts: ["monitoringLed"],
  },
  boxSizeSmall: { position: 1, value: 0, needs: [], donts: ["boxSizeBig"] },
  boxSizeBig: { position: 1, value: 1, needs: [], donts: ["boxSizeSmall"] },
  saveNo: { position: 3, value: 0, needs: [], donts: ["saveYes"] },
  saveYes: { position: 3, value: 1, needs: [], donts: ["saveNo"] },
  colorGray: {
    position: 4,
    value: 1,
    needs: [],
    donts: ["colorWhite", "colorBlack", "colorTransparent"],
  },
  colorWhite: {
    position: 5,
    value: 1,
    needs: [],
    donts: ["colorGray", "colorBlack", "colorTransparent"],
  },
  colorBlack: {
    position: 6,
    value: 1,
    needs: [],
    donts: ["colorGray", "colorWhite", "colorTransparent"],
  },
  colorTransparent: {
    position: 7,
    value: 1,
    needs: [],
    donts: ["colorGray", "colorWhite", "colorBlack"],
  },
};

function MeaningToNumber(prod, m, count) {
  let n = 0;

  // set ver
  n = setBits(n, version);

  // set product number
  n = setBits(n, prod << lengths.ver);

  // set id
  let id = Math.floor(Math.random() * (Math.pow(2, lengths.id) + 1)); // generate random id
  n = setBits(n, id << (lengths.ver + lengths.prod));

  // set count
  n = setBits(n, count << (lengths.ver + lengths.prod + lengths.id));

  // set config
  let config = 0;
  for (let [key, value] of Object.entries(internal))
    if (m.includes(key))
      config = setBits(config, value.value << value.position); // get config data
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
        lengths.congfig)
  );

  return n;
}

function NumberToMeaning(n) {
  let str = "";

  // get parity
  str +=
    "parity: " +
    getBits(
      n,
      lengths.ver + lengths.prod + lengths.id + lengths.count + lengths.congfig,
      lengths.parity
    );
  // remove parity
  n = clearBits(
    n,
    lengths.ver + lengths.prod + lengths.id + lengths.count + lengths.congfig,
    lengths.parity
  );

  console.log("1", n.toString(2));

  // get version
  str += ", ver: " + getBits(n, 0, lengths.ver);
  // remove version
  n = removeBits(n, 0, lengths.ver);

  console.log("2", n.toString(2));

  // get product
  str += ", prod: " + getBits(n, 0, lengths.prod);
  // remove product
  n = removeBits(n, 0, lengths.prod);

  console.log("3", n.toString(2));

  // get ID
  str += ", id: " + getBits(n, 0, lengths.id);
  // remove ID
  n = removeBits(n, 0, lengths.id);

  console.log("4", n.toString(2));

  // get count
  str += ", count: " + getBits(n, 0, lengths.count);
  // remove count
  n = removeBits(n, 0, lengths.count);

  console.log("5", n.toString(2));

  // get config
  for (let [key, value] of Object.entries(internal))
    if (getBit(n, value.position) == value.value) str += ", " + key;

  // n & (value.value << value.position)) == value.value << value.position)

  return str;
}

// #region bit manipulation
const setBits = (n, bits) => n | bits;

const getBit = (n, pos) => (n & (1 << pos)) >> pos;

const getBits = function (n, posStart, count) {
  let bits = 0;
  for (let i = posStart; i < posStart + count; ++i) bits |= getBit(n, i) << i;
  return bits >> posStart;
};

const clearBit = (n, pos) => n & ~(1 << pos);

const clearBits = function (n, posStart, count) {
  for (let i = posStart; i < posStart + count; ++i) n = clearBit(n, i);
  return n;
};

const removeBits = (n, posStart, count) =>
  clearBits(n, posStart, count) >> count;

const getParity = (n) => ((n.toString(2).split("1") ?? []).length - 1) & 1;
// #endregion

console.log("input: " + input.toString());
const output = MeaningToNumber(produktCo2, input, input2);
console.log(
  output + " (" + output.toString(2) + ") => " + NumberToMeaning(output)
);
