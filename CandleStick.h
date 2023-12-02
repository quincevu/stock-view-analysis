#pragma once

using namespace System;
using namespace System::Windows::Forms;
namespace CIS4930 {
    public ref class candleStick
    {
    public:
        property DateTime Date;
        property double Open;
        property double High;
        property double Low;
        property double Close;
        property long Volume;
        static property System::Data::DataTable^ Datasource;
        property double body;
        property double range;

        property double topPrice;
        property double bottomPrice;
        property double upperTail;
        property double lowerTail;

        property bool bullish;
        property bool bearish;
        property bool neutral;

        property bool commonDoji;
        property bool gravestoneDoji;
        property bool neutralDoji;
        property bool dragonflyDoji;
        property bool longLeggedDoji;

        property bool hammer;
        property bool bullishHammer;
        property bool bearishHammer;
        property bool invertedHammer;
        property bool bullishInvertedHammer;
        property bool bearishInvertedHammer;
        property bool marubozu;
        property bool whiteMarubozu;
        property bool blackMarubozu;

        candleStick()
        {
            Date = DateTime::Now;
            Open = 0; Close = 0; High = 0; Low = 0; Volume = 0;
            computeProperties();
        }

        candleStick(DateTime date, double open, double high, double low, double close, long volume)
        {
            Date = date;
            Open = open;
            Close = close;
            High = high;
            Low = low;
            Volume = volume;

            computeProperties();
        }

    public:
        void computePatterns()
        {
            //MessageBox::Show("called");
            bullish = Close > Open;
            bearish = Open > Close;
            neutral = Open == Close;

            commonDoji = dojiTest(0.1);
            dragonflyDoji = dragonflyDojiTest(0.10, 0.15);
            neutralDoji = neutralDojiTest(0.03);
            gravestoneDoji = gravestoneDojiTest(0.03, 0.05);
            longLeggedDoji = longLeggedDojiTest(0.05);

            hammer = hammerTest(0.25, 0.25, 0.05);
            bullishHammer = bullishHammerTest(0.25, 0.25, 0.05);
            bearishHammer = bearishHammerTest(0.25, 0.25, 0.05);
            invertedHammer = invertedHammerTest(0.25, 0.25, 0.05);
            bullishInvertedHammer = bullishInvertedHammerTest(0.25, 0.25, 0.05);
            bearishInvertedHammer = bearishInvertedHammerTest(0.25, 0.25, 0.05);

            marubozu = marubozuTest(0.03);
            whiteMarubozu = whiteMarubozuTest(0.03);
            blackMarubozu = blackMarubozuTest(0.03);

            //MessageBox::Show(bullishHammer.ToString());
        }

        void computeProperties()
        {
            range = High - Low;
            body = Math::Max(Open, Close) - Math::Min(Close, Open);
            topPrice = Math::Max(Open, Close);
            bottomPrice = Math::Min(Open, Close);
            upperTail = High - topPrice;
            lowerTail = bottomPrice - Low;

            computePatterns();
        }

        bool dojiTest(double bodyTolerance)
        {
            return body <= bodyTolerance * range;
        }

        bool dragonflyDojiTest(double bodyTolerance, double upperTailTolerance)
        {
            return dojiTest(bodyTolerance) && (upperTail <= range * upperTailTolerance);
        }

        bool neutralDojiTest(double bodyTolerance)
        {
            return dojiTest(bodyTolerance);
        }

        bool gravestoneDojiTest(double bodyTolerance, double lowerTailTolerance)
        {
            return dojiTest(bodyTolerance) && (lowerTail <= range * lowerTailTolerance);
        }

        bool longLeggedDojiTest(double bodyTolerance)
        {
            return dojiTest(bodyTolerance);
        }

        bool hammerTest(double minBodyTolerance, double maxBodyTolerance, double upperTailTolerance)
        {
            return (minBodyTolerance * range <= body) && (body >= maxBodyTolerance * range) && (upperTail <= upperTailTolerance * range);
        }

        bool bullishHammerTest(double minBodyTolerance, double maxBodyTolerance, double upperTailTolerance)
        {
            return hammerTest(minBodyTolerance, maxBodyTolerance, upperTailTolerance) && (Close > Open);
        }

        bool bearishHammerTest(double minBodyTolerance, double maxBodyTolerance, double upperTailTolerance)
        {
            return hammerTest(minBodyTolerance, maxBodyTolerance, upperTailTolerance) && (Close < Open);
        }

        bool invertedHammerTest(double minBodyTolerance, double maxBodyTolerance, double lowerTailTolerance)
        {
            return (minBodyTolerance * range <= body) && (body >= maxBodyTolerance * range) && (lowerTail <= lowerTailTolerance * range);
        }

        bool bullishInvertedHammerTest(double minBodyTolerance, double maxBodyTolerance, double lowerTailTolerance)
        {
            return invertedHammerTest(minBodyTolerance, maxBodyTolerance, lowerTailTolerance) && bullish == true;
        }

        bool bearishInvertedHammerTest(double minBodyTolerance, double maxBodyTolerance, double lowerTailTolerance)
        {
            return invertedHammerTest(minBodyTolerance, maxBodyTolerance, lowerTailTolerance) && bearish == true;
        }

        bool marubozuTest(double bodyTolerance)
        {
            return body > range * (1 - bodyTolerance);
        }

        bool whiteMarubozuTest(double bodyTolerance)
        {
            return marubozuTest(bodyTolerance) && bullish == true;
        }

        bool blackMarubozuTest(double bodyTolerance)
        {
            return marubozuTest(bodyTolerance) && bearish == true;
        }

        bool engulfingBearishTest()
        {
            return body == 1;
        }

        bool engulfingBullishTest()
        {
            return body == 1;
        }
    };
}

