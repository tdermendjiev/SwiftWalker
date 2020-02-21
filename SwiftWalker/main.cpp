//
//  main.cpp
//  SwiftWalker
//
//  Created by Teodor Dermendzhiev on 14.02.20.
//  Copyright © 2020 Teodor Dermendzhiev. All rights reserved.
//

#include <iostream>
#include <swift/Frontend/Frontend.h>
#include <swift/FrontendTool/FrontendTool.h>
#include "swift/Parse/Lexer.h"

using namespace swift;

void anchorForGetMainExecutable() {}

int main(int argc, const char * argv[]) {
    // insert code here...
        CompilerInvocation Invocation;
    
        Invocation.setMainExecutablePath(
        llvm::sys::fs::getMainExecutable(argv[0],
        reinterpret_cast<void *>(&anchorForGetMainExecutable)));
    
        Invocation.getFrontendOptions().InputsAndOutputs.addInputFile(
            "placeholder");
        Invocation.getLangOptions().AttachCommentsToDecls = true;
        Invocation.getLangOptions().CollectParsedToken = true;
        Invocation.getLangOptions().BuildSyntaxTree = true;
        CompilerInstance CI;
        if (CI.setup(Invocation))
          return 1;
    
        CI.performSema();
        auto &ctx = CI.getASTContext();
        auto swiftUI = ctx.getLoadedModule(ctx.getIdentifier("SwiftUI"));
        if (!swiftUI) {
          llvm::errs() << "error: SwiftUI module not loaded\n";
        }
    
    
    return 0;
}
