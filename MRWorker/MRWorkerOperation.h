//
//  MRWorkerOperation.h
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

typedef void (^MRWorkerOperationOutputBlock)(NSString *output);
typedef void (^MRWorkerOperationCompletionBlock)(int terminationStatus);

/** The `MRWorkerOperation` class encapsulates a single task that can run
 * another program as a subprocess, and provides a simple mechanism for
 * monitoring and interacting with that program. Memory space is not shared
 * between the subprocess and the process that creates it.
 *
 * `MRWorkerOperation` is a subclass of `NSOperation`, and for that reason
 * `MRWorkerOperation` objects are single-shot, meaning they cannot be reused
 * once execution completes. Typically `MRWorkerOperation` objects are executed
 * by adding them directly to an operation queue. This can achieved using an
 * instance of `NSOperationQueue` or by using the convenience class `MRWorker`,
 * which encapsulates an `NSOperationQueue` object.
 *
 */
@interface MRWorkerOperation : NSOperation

/**-----------------------------------------------------------------------------
 * @name Initialising a Worker Operation
 * -----------------------------------------------------------------------------
 */

/** Returns an initialized `MRWorkerOperation` object with the specified launch
 * path, arguments, output block and completion block.
 *
 * @param launchPath The path to the executable.
 * @param arguments An array of `NSString` objects representing arguments to the
 * operation, or `nil` if none required. Arguments should be specified in the
 * same order that they should be passed to the executable.
 * @param outputBlock A block to be called when output is generated by the
 * executable. The block takes the following parameters:
 *
 *   - *output* - Output generated by the executable that was sent to the
 * standard output stream.
 * @param completionBlock A block to be called when the executable terminates.
 * The block takes the following parameters:
 *
 *   - *terminationStatus* - The exit status returned by the executable.
 * @return An initialised worker operation object.
 */
- (instancetype) initWithLaunchPath:(NSString *)launchPath arguments:(NSArray *)arguments outputBlock:(MRWorkerOperationOutputBlock)outputBlock completionBlock:(MRWorkerOperationCompletionBlock)completionBlock;

/**-----------------------------------------------------------------------------
 * @name Creating a Worker Operation
 * -----------------------------------------------------------------------------
 */

/** Returns a worker operation with the specified launch path, arguments, output
 * block and completion block.
 *
 * @param launchPath The path to the executable.
 * @param arguments An array of `NSString` objects representing arguments to the
 * operation, or `nil` if none required. Arguments should be specified in the
 * same order that they should be passed to the executable.
 * @param outputBlock A block to be called when output is generated by the
 * executable. The block takes the following parameters:
 *
 *   - *output* - The output generated by the executable and sent to the
 * standard output stream. It may be necessary to buffer the output as the
 * block may be called repeatedbly during the lifetime of the operation.
 * @param completionBlock A block to be called when the executable terminates.
 * The block takes the following parameters:
 *
 *   - *terminationStatus* - The exit status returned by the executable.
 * @return A new worker operation object.
 */
+ (instancetype)workerOperationWithLaunchPath:(NSString *)launchPath arguments:(NSArray *)arguments outputBlock:(MRWorkerOperationOutputBlock)outputBlock completionBlock:(MRWorkerOperationCompletionBlock)completionBlock;

@end
