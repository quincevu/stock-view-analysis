#pragma once

#include "Recognizer.h"

using namespace System;
using namespace System::Collections::Generic;

namespace CIS4930 {

    ref class EngulfingBullishCandlestick_Recognizer : public aRecognizor {
    public:
        EngulfingBullishCandlestick_Recognizer() : aRecognizor("Bullish Engulfing Pattern", 2) {}

    public:
        virtual bool patternMatchedSubset(List<candleStick^>^ Lcs) override {
            candleStick^ pcs = Lcs[0];
            candleStick^ cs = Lcs[1];
            return pcs->bearish && cs->bullish && pcs->High < cs->topPrice && pcs->Low < cs->bottomPrice;
        }
    };

    ref class EngulfingBearishCandlestick_Recognizer : public aRecognizor {
    public:
        EngulfingBearishCandlestick_Recognizer() : aRecognizor("Bearish Engulfing Pattern", 2) {}

    public:
        virtual bool patternMatchedSubset(List<candleStick^>^ Lcs) override {
            candleStick^ pcs = Lcs[0];
            candleStick^ cs = Lcs[1];
            return pcs->bullish && cs->bullish && pcs->High < cs->topPrice && pcs->Low < cs->bottomPrice;
        }
    };

}
