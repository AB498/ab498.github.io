// express endpoint example:
app.post("/words-count", (req, res) => {
  const inputString = req.body.text;
  // split by one or more spaces
  const words = inputString.split(/\s+/);
  const wordMap = {};

  words.forEach((word) => {
    if (wordMap[word]) {
      wordMap[word] += 1;
    } else {
      wordMap[word] = 1;
    }
  });
  // Time complexity: O(n)
  res.json(wordMap);
});
