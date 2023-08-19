// nextjs api exmaple:
export async function POST(request) {
  try {
    let { email, password } = await request.json();
    // check for duplicate user
    const user = await User.findOne({ email });
    if (user) return "User already exists";

    // hash password using bcryptjs
    const salt = await bcryptjs.genSalt(10);
    const hashedPassword = await bcryptjs.hash(password, salt);
    // self contained hash+salt
    // assuming User is a database model
    await new User({ email, password: hashedPassword }).save();

    return "User created successfully";
  } catch (error) {
    throw new Error("Internal Server Error");
  }
}
