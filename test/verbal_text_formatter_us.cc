#include <regex>

#include "test.h"
#include "valhalla/baldr/verbal_text_formatter.h"
#include "valhalla/baldr/verbal_text_formatter_us.h"

using namespace std;
using namespace valhalla::baldr;

namespace {

// Sub class to test protected methods
class VerbalTextFormatterUsTest : public VerbalTextFormatterUs {
 public:
  VerbalTextFormatterUsTest(const std::string& country_code,
                          const std::string& state_code)
      : VerbalTextFormatterUs(country_code, state_code) {
  }

  std::string FormInterstateTts(const std::string& source) const{
    return VerbalTextFormatterUs::FormInterstateTts(source);
  }

  std::string FormUsHighwayTts(const std::string& source) const{
    return VerbalTextFormatterUs::FormUsHighwayTts(source);
  }

  std::string ProcessStatesTts(const std::string& source) const{
    return VerbalTextFormatterUs::ProcessStatesTts(source);
  }

  std::string FormThousandTts(const std::string& source) const {
    return VerbalTextFormatterUs::FormThousandTts(source);
  }

  std::string FormHundredTts(const std::string& source) const {
    return VerbalTextFormatterUs::FormHundredTts(source);
  }

  std::string FormNumberSplitTts(const std::string& source) const {
    return VerbalTextFormatterUs::FormNumberSplitTts(source);
  }

  std::string FormLeadingOhTts(const std::string& source) const{
    return VerbalTextFormatterUs::FormLeadingOhTts(source);
  }

};

void TryFormInterstateTtsString(string source, string expected) {
  VerbalTextFormatterUsTest formatter_test("US", "PA");
  string tts = formatter_test.FormInterstateTts(source);
  if (tts != expected) {
    throw std::runtime_error(
        "Incorrect FormInterstateTts - EXPECTED: " + expected + "  |  FORMED: " + tts);
  }
}

void TestFormInterstateTtsString() {
  TryFormInterstateTtsString("I H1", "Interstate H1");
  TryFormInterstateTtsString("I 5", "Interstate 5");
  TryFormInterstateTtsString("I 35", "Interstate 35");
  TryFormInterstateTtsString("I 35E", "Interstate 35E");
  TryFormInterstateTtsString("I 35W", "Interstate 35W");
  TryFormInterstateTtsString("I 95 South", "Interstate 95 South");
  TryFormInterstateTtsString("I 270 Spur", "Interstate 270 Spur");
  TryFormInterstateTtsString("I 495 West", "Interstate 495 West");
  TryFormInterstateTtsString("I-695 West", "Interstate 695 West");
  TryFormInterstateTtsString("I-895", "Interstate 895");
  TryFormInterstateTtsString("i-205 East", "Interstate 205 East");
  TryFormInterstateTtsString("WI 129", "WI 129");
}

void TryFormUsHighwayTtsString(string source, string expected) {
  VerbalTextFormatterUsTest formatter_test("US", "PA");
  string tts = formatter_test.FormUsHighwayTts(source);
  if (tts != expected) {
    throw std::runtime_error(
        "Incorrect FormUsHighwayTts - EXPECTED: " + expected + "  |  FORMED: " + tts);
  }
}

void TestFormUsHighwayTtsString() {
  TryFormUsHighwayTtsString("US 1", "U.S. 1");
  TryFormUsHighwayTtsString("US 22", "U.S. 22");
  TryFormUsHighwayTtsString("US 220 North", "U.S. 220 North");
  TryFormUsHighwayTtsString("US-220 South", "U.S. 220 South");
  TryFormUsHighwayTtsString("Us 422 Business Alternate", "U.S. 422 Business Alternate");
  TryFormUsHighwayTtsString("Us-522", "U.S. 522");
}

void TryProcessStatesTts(string source, string expected) {
  VerbalTextFormatterUsTest formatter_test("US", "");
  string tts = formatter_test.ProcessStatesTts(source);
  if (tts != expected) {
    throw std::runtime_error(
        "Incorrect FormUsHighwayTts - EXPECTED: " + expected + "  |  FORMED: " + tts);
  }
}

void TestProcessStatesTts() {
  TryProcessStatesTts("AL 261", "Alabama 261");
  TryProcessStatesTts("AL-261", "Alabama 261");
  TryProcessStatesTts("Al 261", "Alabama 261");
  TryProcessStatesTts("AK 1", "Alaska 1");
}

void TryFormThousandTtsString(string source, string expected) {
  VerbalTextFormatterUsTest formatter_test("US", "PA");
  string tts = formatter_test.FormThousandTts(source);
  if (tts != expected) {
    throw std::runtime_error(
        "Incorrect FormThousandTts - EXPECTED: " + expected + "  |  FORMED: " + tts);
  }
}

void TestFormThousandTtsString() {
  TryFormThousandTtsString("1", "1");
  TryFormThousandTtsString("10", "10");
  TryFormThousandTtsString("1000", "1 thousand");
  TryFormThousandTtsString("MD 1000", "MD 1 thousand");
  TryFormThousandTtsString("MD 1000 West", "MD 1 thousand West");
  TryFormThousandTtsString("24000", "24 thousand");
  TryFormThousandTtsString("MD 24000", "MD 24 thousand");
  TryFormThousandTtsString("MD 24000 West", "MD 24 thousand West");
}

void TryFormHundredTtsString(string source, string expected) {
  VerbalTextFormatterUsTest formatter_test("US", "MD");
  string tts = formatter_test.FormHundredTts(source);
  if (tts != expected) {
    throw std::runtime_error(
        "Incorrect FormHundredTts - EXPECTED: " + expected + "  |  FORMED: " + tts);
  }
}

void TestFormHundredTtsString() {
  TryFormHundredTtsString("1", "1");
  TryFormHundredTtsString("10", "10");
  TryFormHundredTtsString("100", "1 hundred");
  TryFormHundredTtsString("MD 100", "MD 1 hundred");
  TryFormHundredTtsString("MD 100 West", "MD 1 hundred West");
  TryFormHundredTtsString("2400", "24 hundred");
  TryFormHundredTtsString("MD 2400", "MD 24 hundred");
  TryFormHundredTtsString("MD 2400 West", "MD 24 hundred West");
}

void TryFormNumberSplitTtsString(string source, string expected) {
  VerbalTextFormatterUsTest formatter_test("US", "PA");
  string tts = formatter_test.FormNumberSplitTts(source);
  if (tts != expected) {
    throw std::runtime_error(
        "Incorrect FormNumberSplitTts - EXPECTED: " + expected + "  |  FORMED: " + tts);
  }
}

void TestFormNumberSplitTtsString() {
  TryFormNumberSplitTtsString("1", "1");
  TryFormNumberSplitTtsString("12", "12");
  TryFormNumberSplitTtsString("123", "1 23");
  TryFormNumberSplitTtsString("1234", "12 34");
  TryFormNumberSplitTtsString("12345", "1 23 45");
  TryFormNumberSplitTtsString("123456", "12 34 56");
  TryFormNumberSplitTtsString("1234567", "1 23 45 67");
  TryFormNumberSplitTtsString("12345678", "12 34 56 78");
  TryFormNumberSplitTtsString("123456789", "1 23 45 67 89");
  TryFormNumberSplitTtsString("1234567890", "12 34 56 78 90");
  TryFormNumberSplitTtsString("105", "1 05");
  TryFormNumberSplitTtsString("20304", "2 03 04");
  TryFormNumberSplitTtsString("3010203", "3 01 02 03");
  TryFormNumberSplitTtsString("PA 220", "PA 2 20");
  TryFormNumberSplitTtsString("PA 283 West", "PA 2 83 West");
  TryFormNumberSplitTtsString("CR 1155 North", "CR 11 55 North");
  TryFormNumberSplitTtsString("146B", "1 46B");
  TryFormNumberSplitTtsString("1 123456", "1 12 34 56");
  TryFormNumberSplitTtsString("12 123456", "12 12 34 56");
  TryFormNumberSplitTtsString("1 123456 1", "1 12 34 56 1");
  TryFormNumberSplitTtsString("12 123456 1", "12 12 34 56 1");
  TryFormNumberSplitTtsString("123 123456", "1 23 12 34 56");
  TryFormNumberSplitTtsString("123456, 123456", "12 34 56, 12 34 56");
  TryFormNumberSplitTtsString("123456, 123456, 123456", "12 34 56, 12 34 56, 12 34 56");
  TryFormNumberSplitTtsString("County Road 00-122", "County Road 00-1 22");
  TryFormNumberSplitTtsString("Road 0110", "Road 01 10");
  TryFormNumberSplitTtsString("101st Street", "101st Street");
  TryFormNumberSplitTtsString("102nd Street", "102nd Street");
  TryFormNumberSplitTtsString("103rd Street", "103rd Street");
  TryFormNumberSplitTtsString("104th Street", "104th Street");
  TryFormNumberSplitTtsString("101St Street", "101St Street");
  TryFormNumberSplitTtsString("102ND Street", "102ND Street");
}

void TryFormLeadingOhTtsString(string source, string expected) {
  VerbalTextFormatterUsTest formatter_test("US", "PA");
  string tts = formatter_test.FormLeadingOhTts(source);
  if (tts != expected) {
    throw std::runtime_error(
        "Incorrect FormLeadingOhTts - EXPECTED: " + expected + "  |  FORMED: " + tts);
  }
}

void TestFormLeadingOhTtsString() {
  TryFormLeadingOhTtsString("1", "1");
  TryFormLeadingOhTtsString("1 05", "1 o5");
  TryFormLeadingOhTtsString("West 1 05 1st Avenue", "West 1 o5 1st Avenue");
  TryFormLeadingOhTtsString("10 05 03", "10 o5 o3");
  TryFormLeadingOhTtsString("County Road 00-1 22", "County Road 00-1 22");
  TryFormLeadingOhTtsString("County Road 0-30", "County Road 0-30");
  TryFormLeadingOhTtsString("State Highway 0", "State Highway 0");
}

void TryFormat(string source, string expected) {
  VerbalTextFormatterUsTest formatter_test("US", "PA");
  string tts = formatter_test.Format(source);
  if (tts != expected) {
    throw std::runtime_error(
        "Incorrect Format - EXPECTED: " + expected + "  |  FORMED: " + tts);
  }
}

void TestFormat() {
  TryFormat("I H1", "Interstate H1");
  TryFormat("I 5", "Interstate 5");
  TryFormat("I 35", "Interstate 35");
  TryFormat("I 35E", "Interstate 35E");
  TryFormat("I 35W", "Interstate 35W");
  TryFormat("I 95 South", "Interstate 95 South");
  TryFormat("I 270 Spur", "Interstate 2 70 Spur");
  TryFormat("I 495 West", "Interstate 4 95 West");
  TryFormat("I-695 West", "Interstate 6 95 West");
  TryFormat("I-895", "Interstate 8 95");
  TryFormat("i-205 East", "Interstate 2 o5 East");

  TryFormat("US 1", "U.S. 1");
  TryFormat("US 22", "U.S. 22");
  TryFormat("US 220 North", "U.S. 2 20 North");
  TryFormat("US-220 South", "U.S. 2 20 South");
  TryFormat("US 202", "U.S. 2 o2");
  TryFormat("Us 422 Business Alternate", "U.S. 4 22 Business Alternate");
  TryFormat("Us-522", "U.S. 5 22");

  TryFormat("AL 233", "Alabama 2 33");
  TryFormat("PA 23", "Pennsylvania 23");
  TryFormat("PA 283", "Pennsylvania 2 83");
  TryFormat("PA 100", "Pennsylvania 1 hundred");
  TryFormat("PA 1080", "Pennsylvania 10 80");
  TryFormat("PA 4007", "Pennsylvania 40 o7");
  TryFormat("SR 1021", "SR 10 21");
  TryFormat("SR-1021", "SR-10 21");
  TryFormat("Sr 1021", "Sr 10 21");
  TryFormat("SR3032", "SR30 32");

  TryFormat("T609", "T6 o9");
}

}

int main() {
  test::suite suite("verbal_text_formatter_us");

  // FormInterstateTts
  suite.test(TEST_CASE(TestFormInterstateTtsString));

  // FormUsHighwayTtsString
  suite.test(TEST_CASE(TestFormUsHighwayTtsString));

  // ProcessStatesTts
  suite.test(TEST_CASE(TestProcessStatesTts));

  // FormThousandTtsString
  suite.test(TEST_CASE(TestFormThousandTtsString));

  // FormHundredTtsString
  suite.test(TEST_CASE(TestFormHundredTtsString));

  // FormNumberSplitTtsString
  suite.test(TEST_CASE(TestFormNumberSplitTtsString));

  // FormLeadingOhTtsString
  suite.test(TEST_CASE(TestFormLeadingOhTtsString));

  // Format
  suite.test(TEST_CASE(TestFormat));

  return suite.tear_down();
}
