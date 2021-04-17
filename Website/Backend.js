const internal = {
  monitoringLed: 1 << 0,
  monitoringDisplay: 1 << 1,
  boxSizeSmall: 1 << 2,
  boxSizeBig: 1 << 3,
  cableSizeOneM: 1 << 4,
  cableSizeTwoM: 1 << 5,
  saveNo: 1 << 6,
  saveYes: 1 << 7,
};

function MeaningToNumberV1(m) {
  let n = 0;

  // set values
  for (let key of m) n = n | internal[key];

  // set id
  for (let i = 0; i < 6; ++i)
    n = Math.random() > 0.5 ? n | (1 << (Object.keys(internal).length + i)) : n;

  return n;
}

function NumberToMeaning(n) {
  let str = "";

  // get values
  for (let [key, value] of Object.entries(internal))
    if ((n & value) == value) str += key + ", ";

  // get ID
  let id = n;
  id = id >> Object.keys(internal).length;
  id = id << Object.keys(internal).length;
  str += "id: " + id;

  return str;
}

let input = ["monitoringLed", "boxSizeSmall", "cableSizeOneM", "saveNo"];

console.log("input: " + input.toString());
const output1 = MeaningToNumberV1(input);
console.log("number: " + output1);
console.log("number to string conversion: " + NumberToMeaning(output1));
