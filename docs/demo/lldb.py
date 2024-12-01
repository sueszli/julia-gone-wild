import lldb


def trace_calls(frame, bp_loc, dict):
    func_name = frame.GetFunctionName()
    print("function call:", func_name)
    return False


debugger = lldb.debugger
target = debugger.GetSelectedTarget()

for module in target.module_iter():
    for symbol in module:
        if symbol.GetType() == lldb.eSymbolTypeCode:
            bp = target.BreakpointCreateBySBAddress(symbol.GetStartAddress())
            bp.SetScriptCallbackFunction("trace_calls")

command_interpreter = debugger.GetCommandInterpreter()
return_object = lldb.SBCommandReturnObject()
command_interpreter.HandleCommand("process continue", return_object)
print(return_object.GetOutput())
