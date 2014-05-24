//
//  MRWorkerOperation+Private.h
//  MRWorker
//
//  Copyright (c) 2014 Marc Ransome <marc.ransome@fidgetbox.co.uk>
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to
//  deal in the Software without restriction, including without limitation the
//  rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
//  sell copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.
//

#import <Foundation/Foundation.h>
#import "MRWorkerOperation.h"

typedef NS_ENUM(NSInteger, MRWorkerTaskTerminationMode) {
    MRWorkerTaskTerminationModeInterrupt,
    MRWorkerTaskTerminationModeTerminate,
    MRWorkerTaskTerminationModeKill
};

@interface MRWorkerOperation ()
{
    BOOL _executing;
    BOOL _finished;
    void (^_outputBlock)(NSString *);
    void (^_completionBlock)(int);
}

@property (nonatomic, strong) NSTask *task;
@property (nonatomic, strong) NSDate *taskTerminationTime;
@property (nonatomic, assign) MRWorkerTaskTerminationMode taskTerminationMode;

@end