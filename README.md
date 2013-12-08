## MRWorker

A simple example:

```objc
MRWorkerOperation *operation = [MRWorkerOperation workerOperationWithLaunchPath:@"/bin/ls" arguments:@[@"-al", @"/"] outputBlock:^(NSString *output) {
    ...
} completionBlock:^(int terminationStatus) {
    ...
}
    
[[MRWorkerOperationQueue sharedQueue] addOperation:operation];
```

## License
`MRWorker` is provided under the terms of the [MIT License](http://opensource.org/licenses/mit-license.php).

## Contact
Email me at [marc.ransome@fidgetbox.co.uk](mailto:marc.ransome@fidgetbox.co.uk) or tweet [@marcransome](http://www.twitter.com/marcransome).
