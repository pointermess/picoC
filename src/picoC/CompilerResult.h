#pragma once

#include <memory>
#include <vector>
#include <string>


namespace PicoC
{
    namespace Representation
    {
        enum CompilerHintType { Comment, Warning, Error };
        struct CompilerHint
        {
        public:
            CompilerHintType Type;
            unsigned int Line = 0;
            unsigned int Position = 0;
            std::string Text = "UNDEFINED";
        };


        // Waiting = Not running yet
        // Running = Currently running / Paused
        // Failed = Fatal or syntax error detected
        // Successful = Parsing process completed
        enum CompilerState
        {
            Waiting,
            Running,
            Failed,
            Succesful
        };


        class CompilerResult
        {
        public:
            std::vector<CompilerHint> Hints;
            void AddHint(CompilerHint hint) { Hints.push_back(hint); };

            CompilerState State;

            CompilerResult() { State = Waiting; };
        };
        typedef std::shared_ptr<CompilerResult> CompilerResultPtr;
    }
}