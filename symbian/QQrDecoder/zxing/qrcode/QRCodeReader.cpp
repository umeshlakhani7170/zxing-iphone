/*
 *  QRCodeReader.cpp
 *  zxing
 *
 *  Created by Christian Brunschen on 20/05/2008.
 *  Copyright 2008 ZXing authors All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <zxing/qrcode/QRCodeReader.h>
#include <zxing/qrcode/detector/Detector.h>

#include <iostream>

namespace zxing {
	namespace qrcode {
		
		using namespace std;
		
		QRCodeReader::QRCodeReader() :decoder_() {
		}
		
		Ref<Result> QRCodeReader::decode(Ref<BinaryBitmap> image) {
#ifdef DEBUG
			cout << "decoding image " << image.object_ << ":\n" ;
#endif
			
			Detector detector(image->getBlackMatrix());
			
			
#ifdef DEBUG
			cout << "(1) created detector " << &detector << "\n" ;
#endif
			
			Ref<DetectorResult> detectorResult(detector.detect());
#ifdef DEBUG
			cout << "(2) detected, have detectorResult " << detectorResult.object_ << "\n" ;
#endif
			
			std::vector<Ref<ResultPoint> > points(detectorResult->getPoints());
			
			
#ifdef DEBUG
			cout << "(3) extracted points " << &points << "\n";
			cout << "found " << points.size() << " points:\n";
			for (size_t i = 0; i < points.size(); i++) {
				cout << "   " << points[i]->getX() << "," << points[i]->getY() << "\n";
			}
			cout << "bits:\n";
			cout << *(detectorResult->getBits()) << "\n";
#endif
			
			Ref<DecoderResult> decoderResult(decoder_.decode(detectorResult->getBits()));
#ifdef DEBUG
			cout << "(4) decoded, have decoderResult " << decoderResult.object_ << "\n" ;
#endif
			
			Ref<Result> result(
							   new Result(decoderResult->getText(), decoderResult->getRawBytes(), points, BarcodeFormat_QR_CODE));
#ifdef DEBUG
			cout << "(5) created result " << result.object_ << ", returning\n" ;
			
			cout << "(6) text: " << result->getText()->getText() << std::endl;
#endif
			
			return result;
		}
		
		QRCodeReader::~QRCodeReader() {
		}
		
	}
}
