const app = require('express')();

app.use("/", require("express").static("./"));

app.listen(3000, () => console.log('Listening on http://localhost:3000/'));