#include "pch.h"
#include "CppUnitTest.h"
#include<string>
#include"..//DecodeHoffmanAlgorythm/HoffmanAlgo.h"
#include"..//DecodeHoffmanAlgorythm/Map.h"
#include"..//DecodeHoffmanAlgorythm/List.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitForHoffman
{
	TEST_CLASS(UnitForHoffman)
	{
	public:
		TEST_METHOD(TestCodingHoffman_different_symbol_words)
		{
			string str = "Hello";
			string coding_str;
			HoffmanCodingAlgorythm* alg = new HoffmanCodingAlgorythm(str);
			Map<char, string>* hoffman = alg->getTreeAsCode();
			int counter = 0;
			List<Pair<char, int>>* list_symbol = alg->get_list_symbol();
			for (int i = 0; i < str.size(); i++)
				coding_str += hoffman->find(str[i]);
			Assert::AreEqual(coding_str, string("1011100110"));
		}

		TEST_METHOD(TestCodingHoffman_same_symbol_words)
		{
			string str = "fff";//
			string coding_str;
			HoffmanCodingAlgorythm* alg = new HoffmanCodingAlgorythm(str);
			Map<char, string>* hoffman = alg->getTreeAsCode();
			int counter = 0;
			List<Pair<char, int>>* list_symbol = alg->get_list_symbol();
			for (int i = 0; i < str.size(); i++)
				coding_str += hoffman->find(str[i]);
			Assert::AreEqual(coding_str, string("000"));
		}

		TEST_METHOD(TestCodingHoffman_text) {
			string str = "it is string";//
			string coding_str;
			HoffmanCodingAlgorythm* alg = new HoffmanCodingAlgorythm(str);
			Map<char, string>* hoffman = alg->getTreeAsCode();
			int counter = 0;
			List<Pair<char, int>>* list_symbol = alg->get_list_symbol();
			for (int i = 0; i < str.size(); i++)
				coding_str += hoffman->find(str[i]);
			Assert::AreEqual(coding_str, string("101110010110001101110111100110010"));
		}
	};
}