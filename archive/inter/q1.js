// expressjs server example:
app.post("/total-cost", async (req, res) => {
  // assuming the list of productIds given is same as cart of the user
  const productIds = req.body.productIds;
  let totalPrice = 0;
  try {
    // assuming 'Product' is a database model, fetch the details on all products
    const products = await Product.findAll({
      where: { id: productIds },
    });
    for (const product of products) {
      // assuming 'runningDiscountPercentage' is product's own current discount
      const discountedPrice =
        (product.price * (100 - product.runningDiscountPercentage)) / 100;
      totalPrice += discountedPrice;
    }
    res.json({ totalPrice });
  } catch (error) {
    res.status(500).json({ error: "Internal Server Error" });
  }
});
