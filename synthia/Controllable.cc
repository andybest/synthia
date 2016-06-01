/*

MIT License
 
Copyright (c) 2016 Andy Best

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#include "Controllable.h"

#include <math.h>
namespace Synthia
{
    
    bool Controllable::addControlEntry(ControlEntryId id, string name, ControlType type, float minValue, float maxValue)
    {
        ControlEntry entry;
        entry.id = id;
        entry.name = name;
        entry.type = type;
        entry.rangeLow = minValue;
        entry.rangeHigh = maxValue;
        
        
        if(_controlEntries.count(id) > 0)
        {
            // This ID already exists!
            return false;
        }
        
        _controlEntries[id] = entry;
        return true;
    }
    
    bool Controllable::setControlWithMidiCCValue(ControlEntryId id, unsigned char value)
    {
        // An entry with the id given does not exist
        if(_controlEntries.count(id) == 0)
            return false;
        
        ControlEntry entry = _controlEntries[id];
        
        float val = convertFromMidiCCValue(value, entry);
        changeValueForControlId(id, val);
        
        return true;
    }
    
    float Controllable::convertFromMidiCCValue(unsigned char value, ControlEntry entry)
    {
        switch (entry.type)
        {
            case kControlTypeFloatZeroOne:
                return (value & 0x7F) / 127.0f;
                
            case kControlTypeFloatCustomRange:
            {
                float normalized = (value & 0x7F) / 127.0f;
                float difference = entry.rangeHigh - entry.rangeLow;
                return entry.rangeLow + (normalized * difference);
            }
                
            case kControlTypeFloatZeroOneLogarithmic:
                return log10f((((value & 0x7F) / 127.0f) * 9) + 1);
                
            case kControlTypeFloatCustomRangeLogarithmic:
            {
                float normalized = log10f((((value & 0x7F) / 127.0f) * 9) + 1);
                float difference = entry.rangeHigh - entry.rangeLow;
                return entry.rangeLow + (normalized * difference);
            }
        }
        
        return 0.0f;
    }
    
    
}