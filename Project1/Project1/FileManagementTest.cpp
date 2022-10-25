#include "pch.h"

TEST(FileManagement, getInputDirectory) {
	std::string input = "C:\\Users\\Test\\Documents\\Input";

	FileManagement f1(input, "", "");

	std::string result = f1.getInputDirectory();

	EXPECT_EQ(result, input);
}
TEST(FileManagement, getIntermediateDirectory) {

	std::string input = "C:\\Users\\Test\\Documents\\Intermediate";

	FileManagement f1("", input, "");

	std::string result = f1.getIntermediateDirectory();

	EXPECT_EQ(result, input);
}
TEST(FileManagement, getOutputDirectory) {
	std::string input = "C:\\Users\\Test\\Documents\\Output";

	FileManagement f1("", "", input);

	std::string result = f1.getOutputDirectory();

	EXPECT_EQ(result, input);
}
TEST(FileManagement, setInputDirectory) {
	std::string input = "C:\\Users\\Test\\Documents\\Input";

	FileManagement f1;

	f1.setInputDirectory(input);

	std::string result = f1.getInputDirectory();

	EXPECT_EQ(result, input);
}
TEST(FileManagement, setIntermediateputDirectory) {
	std::string input = "C:\\Users\\Test\\Documents\\Intermediate";

	FileManagement f1;

	f1.setIntermediateDirectory(input);

	std::string result = f1.getIntermediateDirectory();

	EXPECT_EQ(result, input);
}
TEST(FileManagement, setOutputDirectory) {
	std::string input = "C:\\Users\\Test\\Documents\\Output";

	FileManagement f1;

	f1.setOutputDirectory(input);

	std::string result = f1.getOutputDirectory();

	EXPECT_EQ(result, input);
}
TEST(FileManagement, EndOfFileTrue) {
	FileManagement f1;

	std::string dir = DIR;
	std::string fileA = FILE_A;
	std::string temp;

	temp = f1.readFile(dir, fileA);
	temp = f1.readFile(dir, fileA);
	temp = f1.readFile(dir, fileA);

	bool result = f1.EndOfFile(fileA);

	EXPECT_TRUE(result);
}

TEST(FileManagement, EndOfFileFalse) {
	FileManagement f1;

	bool result = f1.EndOfFile("testfile.txt");

	EXPECT_FALSE(result);
}
TEST(FileManagement, verifyDirectoryFalse) {
	FileManagement f1;

	bool result = f1.verify_directory("");

	EXPECT_FALSE(result);
}
TEST(FileManagement, verifyDirectoryTrue) {
	FileManagement f1;
	
	std::string dir = DIR;

	bool result = f1.verify_directory(dir);

	EXPECT_TRUE(result);
}

TEST(FileManagement, listFiles) {
	FileManagement f1;

	std::string dir = DIR;
	std::string dirA = DIR_A;
	std::string fileA = FILE_A;
	std::string fileB = FILE_B;
	
	std::vector<std::string> files;
	files.push_back(dirA);
	files.push_back(fileA);
	files.push_back(fileB);
	files.push_back("SUCCESS.txt");

	std::vector<std::string> result = f1.list_files(dir);

	EXPECT_EQ(result, files);
}

TEST(FileManagement, readFile) {
	FileManagement f1;

	std::string dir = DIR;
	std::string fileA = FILE_A;
	std::string conA = CON_A;

	std::string result = f1.readFile(dir, fileA);

	EXPECT_EQ(result, conA);
}

TEST(FileManagement, writeFileSuccess) {
	FileManagement f1;

	std::string dir = DIR;
	std::string file = "SUCCESS.txt";

	bool result = f1.writeFileSuccess(dir, file);

	EXPECT_TRUE(result);
}

TEST(FileManagement, writeFile) {
	FileManagement f1;

	std::string dir = DIR;
	std::string fileB = FILE_B;

	std::vector<int> count_c;
	count_c.push_back(1);
	count_c.push_back(1);
	count_c.push_back(1);
	count_c.push_back(1);
	std::string word_c = "b";
	
	std::vector <std::pair<std::string, std::vector<int>>> output_lines;
	output_lines.push_back(std::pair<std::string, std::vector<int>>(word_c, count_c));

	f1.writeFile(output_lines, dir, fileB);

	std::string result = f1.readFile(dir, fileB);

	EXPECT_EQ(result, "(\"b\", [1, 1, 1, 1])");

	std::fstream ofs;
	std::string path = dir + fileB;
	ofs.open(path, std::ios::out | std::ios::trunc);
}

int main(int args, char* argv[]) {
	testing::InitGoogleTest(&args, argv);
	return RUN_ALL_TESTS();
}