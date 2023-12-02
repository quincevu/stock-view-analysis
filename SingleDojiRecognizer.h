#pragma once

#include "Recognizer.h"
#include "CandleStick.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;

namespace CIS4930 {

    // Bullish pattern recognizer class
    ref class Recognizer_Bullish : public aRecognizor {
    public:
        Recognizer_Bullish() : aRecognizor("Bullish", 1) { }

    public:
        virtual bool patternMatchedSubset(List<candleStick^>^ subsetOfCandlesticks) override {
            MessageBox::Show("Here");
            return subsetOfCandlesticks[0]->bullish;
        }
    };

    // Bearish pattern recognizer class
    ref class Recognizer_Bearish : public aRecognizor {
    public:
        Recognizer_Bearish() : aRecognizor("Bearish", 1) {}

    public:
        virtual bool patternMatchedSubset(List<candleStick^>^ subsetOfCandlesticks) override {
            return subsetOfCandlesticks[0]->bearish;
        }
    };

    // Neutral pattern recognizer class
    ref class Recognizer_Neutral : public aRecognizor {
    public:
        Recognizer_Neutral() : aRecognizor("Neutral", 1) {}

    public:
        virtual bool patternMatchedSubset(List<candleStick^>^ subsetOfCandlesticks) override {
            return subsetOfCandlesticks[0]->neutral;
        }
    };

    // Doji pattern recognizer class
    ref class Recognizer_Doji : public aRecognizor {
    public:
        Recognizer_Doji() : aRecognizor("Doji", 1) {}

    public:
        virtual bool patternMatchedSubset(List<candleStick^>^ subsetOfCandlesticks) override {
            return subsetOfCandlesticks[0]->commonDoji;
        }
    };

    // Dragonfly Doji pattern recognizer class
    ref class Recognizer_DragonFly : public aRecognizor {
    public:
        Recognizer_DragonFly() : aRecognizor("Dragonfly", 1) {}

    public:
        virtual bool patternMatchedSubset(List<candleStick^>^ subsetOfCandlesticks) override {
            return subsetOfCandlesticks[0]->dragonflyDoji;
        }
    };

    // Neutral Doji pattern recognizer class
    ref class Recognizer_NeutralDoji : public aRecognizor {
    public:
        Recognizer_NeutralDoji() : aRecognizor("Neutral Doji", 1) {}

    public:
        virtual bool patternMatchedSubset(List<candleStick^>^ subsetOfCandlesticks) override {
            return subsetOfCandlesticks[0]->neutralDoji;
        }
    };

    // Gravestone Doji pattern recognizer class
    ref class Recognizer_GravestoneDoji : public aRecognizor {
    public:
        Recognizer_GravestoneDoji() : aRecognizor("Gravestone Doji", 1) {}

    public:
        virtual bool patternMatchedSubset(List<candleStick^>^ subsetOfCandlesticks) override {
            return subsetOfCandlesticks[0]->gravestoneDoji;
        }
    };

    // Long Legged Doji pattern recognizer class
    ref class Recognizer_longLeggedDoji : public aRecognizor {
    public:
        Recognizer_longLeggedDoji() : aRecognizor("LongLegged Doji", 1) {}

    public:
        virtual bool patternMatchedSubset(List<candleStick^>^ subsetOfCandlesticks) override {
            return subsetOfCandlesticks[0]->longLeggedDoji;
        }
    };

    // Hammer pattern recognizer class
    ref class Recognizer_Hammer : public aRecognizor {
    public:
        Recognizer_Hammer() : aRecognizor("Hammer", 1) {}

    public:
        virtual bool patternMatchedSubset(List<candleStick^>^ subsetOfCandlesticks) override {
            return subsetOfCandlesticks[0]->hammer;
        }
    };

    // Bullish Hammer pattern recognizer class
    ref class Recognizer_BullishHammer : public aRecognizor {
    public:
        Recognizer_BullishHammer() : aRecognizor("Bullish Hammer", 1) {}

    public:
        virtual bool patternMatchedSubset(List<candleStick^>^ subsetOfCandlesticks) override {
            return subsetOfCandlesticks[0]->bullishHammer;
        }
    };

    // Bearish Hammer pattern recognizer class
    ref class Recognizer_BearishHammer : public aRecognizor {
    public:
        Recognizer_BearishHammer() : aRecognizor("Bearish Hammer", 1) {}

    public:
        virtual bool patternMatchedSubset(List<candleStick^>^ subsetOfCandlesticks) override {
            return subsetOfCandlesticks[0]->bearishHammer;
        }
    };

    // Inverted Hammer pattern recognizer class
    ref class Recognizer_invertedHammer : public aRecognizor {
    public:
        Recognizer_invertedHammer() : aRecognizor("Inverted Hammer", 1) {}

    public:
        virtual bool patternMatchedSubset(List<candleStick^>^ subsetOfCandlesticks) override {
            return subsetOfCandlesticks[0]->invertedHammer;
        }
    };

    // Bullish Inverted Hammer pattern recognizer class
    ref class Recognizer_bullishInvertedHammer : public aRecognizor {
    public:
        Recognizer_bullishInvertedHammer() : aRecognizor("Bullish Inverted Hammer", 1) {}

    public:
        virtual bool patternMatchedSubset(List<candleStick^>^ subsetOfCandlesticks) override {
            return subsetOfCandlesticks[0]->bullishInvertedHammer;
        }
    };

    // Bearish Inverted Hammer pattern recognizer class
    ref class Recognizer_bearishInvertedHammer : public aRecognizor {
    public:
        Recognizer_bearishInvertedHammer() : aRecognizor("Bearish Inverted Hammer", 1) {}

    public:
        virtual bool patternMatchedSubset(List<candleStick^>^ subsetOfCandlesticks) override {
            return subsetOfCandlesticks[0]->bearishInvertedHammer;
        }
    };

    // Marubozu pattern recognizer class
    ref class Recognizer_Marubozu : public aRecognizor {
    public:
        Recognizer_Marubozu() : aRecognizor("Marubozu", 1) {}

    public:
        virtual bool patternMatchedSubset(List<candleStick^>^ subsetOfCandlesticks) override {
            return subsetOfCandlesticks[0]->marubozu;
        }
    };

    // White Marubozu pattern recognizer class
    ref class Recognizer_whiteMarubozu : public aRecognizor {
    public:
        Recognizer_whiteMarubozu() : aRecognizor("White Marubozu", 1) {}

    public:
        virtual bool patternMatchedSubset(List<candleStick^>^ subsetOfCandlesticks) override {
            return subsetOfCandlesticks[0]->whiteMarubozu;
        }
    };

    // Black Marubozu pattern recognizer class
    ref class Recognizer_blackMarubozu : public aRecognizor {
    public:
        Recognizer_blackMarubozu() : aRecognizor("Black Marubozu", 1) {}

    public:
        virtual bool patternMatchedSubset(List<candleStick^>^ subsetOfCandlesticks) override {
            return subsetOfCandlesticks[0]->blackMarubozu;
        }
    };

}
