const csv = require("csv-parser");
const fs = require("fs");
const results = [];

fs.createReadStream("sales_data.csv")
  .pipe(csv())
  .on("data", (data) => results.push(data))
  .on("end", () => {
    const productRevenue = {};
    results.forEach((record) => {
      const { ProductName, quantitySold, pricePerUnit } = record;
      const revenue = parseFloat(quantitySold) * parseFloat(pricePerUnit);

      if (productRevenue[ProductName]) {
        productRevenue[ProductName] += revenue;
      } else {
        productRevenue[ProductName] = revenue;
      }
    });

    const sortedProducts = Object.entries(productRevenue).sort(
      (a, b) => b[1] - a[1]
    );

    sortedProducts.forEach(([product, revenue]) => {
      console.log(`Total Revenue for ${product}: BDT ${revenue.toFixed(2)}`);
    });
  });
