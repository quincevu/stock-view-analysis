#pragma once

#include "CandleStick.h" // Assuming you have a header file for candleStick class

using namespace System;
using namespace System::Collections::Generic;

namespace CIS4930 {

    public ref class aRecognizor abstract {
    public:
        property String^ patternName; // Public property representing the name of the pattern being recognized
        property int patternSize; // Public property representing the size of the pattern being recognized

        // Abstract method to be implemented by derived classes
        virtual bool patternMatchedSubset(List<candleStick^>^ subsetOfCandlestick) abstract;

        // Public method to recognize the pattern in the given list of candleSticks
        List<int>^ recognize(List<candleStick^>^ candleSticks) {
            List<int>^ result = gcnew List<int>(candleSticks->Count / 8); // Create a new list to store the indices where the pattern is recognized
            int offset = patternSize - 1; // Calculate the offset based on the pattern size
            //MessageBox::Show(offset.ToString());
            for (int i = offset; i < candleSticks->Count; i++) { // Iterate over the candleSticks list, creating subsets of size patternSize
                List<candleStick^>^ subset = candleSticks->GetRange(i - offset, patternSize); // Get a subset of candleSticks of size patternSize starting from index i - offset
                MessageBox::Show(subset->ToString());
                if (patternMatchedSubset(subset)) { // Call the patternMatchedSubset method on the subset of candleSticks to check if it matches the pattern
                    MessageBox::Show("Matched");
                    result->Add(i); // If the pattern is matched, add the index of the last candleStick in the subset to the result list
                }
            }
            return result; // Return the list of indices where the pattern is recognized
        }

        // Constructor to initialize patternName and patternSize properties
        aRecognizor(String^ pName, int pSize) {//check if something goes wrong
            patternName = pName;
            patternSize = pSize;
        }

    };
}
