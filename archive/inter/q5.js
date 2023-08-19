const express = require("express");
const multer = require("multer");
const path = require("path");
const fs = require("fs");

const app = express();
const port = 3000; // Set your desired port
const fileSizeLimit = 1024 * 1024 * 10; // 10 MB

const storage = multer.diskStorage({
  destination: (req, file, cb) => {
    cb(null, "uploads/"); // destination folder
  },
  filename: (req, file, cb) => {
    cb(null, file.originalname); // Keep the original filename
  },
});
const upload = multer({
  storage: storage,
  fileFilter: (req, file, cb) => {
    const allowedTypes = /jpeg|jpg|png|gif/; // Allowed file types
    const extname = allowedTypes.test(
      path.extname(file.originalname).toLowerCase()
    );
    const mimetype = allowedTypes.test(file.mimetype);
    const uploadedFilePath = path.join("uploads/", file.originalname);
    if (fs.existsSync(uploadedFilePath)) {
      // Check if file already exists
      req.fileUploadError = "File already exists.";
      return cb(null, false);
      return;
    }

    if (extname && mimetype) {
      cb(null, true);
    } else {
      req.fileUploadError = "Only images (jpeg, jpg, png, gif) are allowed.";
      return cb(null, false);
    }
  },
  limits: {
    fileSize: fileSizeLimit,
  },
}).array("files", 10); // Allow up to 10 files to be uploaded

app.use(express.static("public"));

app.post("/upload", upload, (req, res, next) => {
  if (req.fileUploadError) {
    console.log(req.fileUploadError);
    return res.status(400).json({ error: req.fileUploadError });
  }
  console.log("req.files");
  const uploadedFiles = req.files;
  if (!uploadedFiles || uploadedFiles.length === 0) {
    return res.status(400).json({ error: "No files uploaded." });
  }

  uploadedFiles.forEach((file) => {
    console.log(file);
    const uploadedFilePath = path.join("uploads/", file.originalname);
    const stats = fs.statSync(uploadedFilePath);
    const fileSizeInBytes = stats.size;

    // Check for size limit
    if (fileSizeInBytes > fileSizeLimit) {
      fs.unlinkSync(uploadedFilePath); // Delete the uploaded file
      return res.status(400).json({
        error: `Size exceeds limit.`,
      });
    }
  });

  return res.json({ message: "Files uploaded successfully." });
});
app.get("/", (req, res) => {
  res.sendFile(__dirname + "/index.html");
});
// handle errors thrown by multer middleware
app.use((err, req, res, next) => {
  return res
    .status(500)
    .json({ error: "Internal Server Error", message: err.message });
});
app.listen(port, () => {
  console.log(`Server is running on port ${port}`);
});
