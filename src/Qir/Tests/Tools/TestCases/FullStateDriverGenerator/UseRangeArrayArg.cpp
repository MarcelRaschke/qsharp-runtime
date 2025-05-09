//----------------------------------------------------------------------------------------------------------------------
// <auto-generated />
// This code was generated by the Microsoft.Quantum.Qir.Runtime.Tools package.
// The purpose of this source code file is to provide an entry-point for executing a QIR program.
// It handles parsing of command line arguments, and it invokes an entry-point function exposed by the QIR program.
//----------------------------------------------------------------------------------------------------------------------

#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

#include "CLI11.hpp"

using namespace std;

// Auxiliary functions for interop with Q# Array type.
struct InteropArray
{
    int64_t Size;
    void* Data;

    InteropArray(int64_t size, void* data) :
        Size(size),
        Data(data){}
};

template<typename T>
unique_ptr<InteropArray> CreateInteropArray(vector<T>& v)
{
    unique_ptr<InteropArray> array(new InteropArray(v.size(), v.data()));
    return array;
}

template<typename S, typename D>
void TranslateVector(vector<S>& sourceVector, vector<D>& destinationVector, function<D(S&)> translationFunction)
{
    destinationVector.resize(sourceVector.size());
    transform(sourceVector.begin(), sourceVector.end(), destinationVector.begin(), translationFunction);
}

// Auxiliary functions for interop with Q# Range type.
using RangeTuple = tuple<int64_t, int64_t, int64_t>;
struct InteropRange
{
    int64_t Start;
    int64_t Step;
    int64_t End;

    InteropRange() :
        Start(0),
        Step(0),
        End(0){}

    InteropRange(RangeTuple rangeTuple) :
        Start(get<0>(rangeTuple)),
        Step(get<1>(rangeTuple)),
        End(get<2>(rangeTuple)){}
};

unique_ptr<InteropRange> CreateInteropRange(RangeTuple rangeTuple)
{
    unique_ptr<InteropRange> range(new InteropRange(rangeTuple));
    return range;
}

InteropRange* TranslateRangeTupleToInteropRangePointer(RangeTuple& rangeTuple)
{
    InteropRange* range = new InteropRange(rangeTuple);
    return range;
}

// Auxiliary functions for interop with Q# Range[] type
template<typename T>
void FreePointerVector(vector<T*>& v)
{
    for (auto p : v)
    {
        delete p;
    }
}

extern "C" void UseRangeArrayArg(
    InteropArray* RangeArrayArg
); // QIR interop function.

int main(int argc, char* argv[])
{
    CLI::App app("QIR Standalone Entry Point");

    // Add a command line option for each entry-point parameter.
    vector<RangeTuple> RangeArrayArgCli;
    app.add_option("--RangeArrayArg", RangeArrayArgCli, "Option to provide a value for the RangeArrayArg parameter")
        ->required();

    // After all the options have been added, parse arguments from the command line.
    CLI11_PARSE(app, argc, argv);

    // Cast parsed arguments to its interop types.
    vector<InteropRange*> RangeArrayArgIntermediate;
    TranslateVector<RangeTuple, InteropRange*>(RangeArrayArgCli, RangeArrayArgIntermediate, TranslateRangeTupleToInteropRangePointer);
    unique_ptr<InteropArray> RangeArrayArgUniquePtr = CreateInteropArray(RangeArrayArgIntermediate);
    InteropArray* RangeArrayArgInterop = RangeArrayArgUniquePtr.get();

    // Execute the entry point operation.
    UseRangeArrayArg(
        RangeArrayArgInterop
    );

    // Flush the output of the simulation.
    cout.flush();

    return 0;
}
