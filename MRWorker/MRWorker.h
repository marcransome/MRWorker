//
//  MRWorker.h
//  MRWorker
//
//  Copyright (c) 2013 Marc Ransome <marc.ransome@fidgetbox.co.uk>
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

@class MRWorkerOperation;


/** The `MRWorker` class encapsulates an `NSOperationQueue` object and regulates
 * the execution of `MRWorkerOperation` objects.
 */
@interface MRWorker : NSObject

/**-----------------------------------------------------------------------------
 * @name Getting the Worker Operation Queue
 * -----------------------------------------------------------------------------
 */

/** Returns the single `MRWorker` instance for the application, creating it if
 * necessary.
 *
 * @return The `MRWorker` instance for the application.
 */
+ (MRWorker *)sharedWorker;


/**-----------------------------------------------------------------------------
 * @name Performing Operations
 * -----------------------------------------------------------------------------
 */

/** Performs an operation.
 *
 * Operations are placed in a queue and will execute concurrently in separate
 * threads.
 *
 * @param operation The operation to perform.
 */
- (void)addOperation:(MRWorkerOperation *)operation;

@end
