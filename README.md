# clickpy

A library able to control mouse (mainly for auto-clicking)

## Installation

> [!WARNING]
> The package will be installed on non-Windows platforms with no errors.
> 
> This is for automation purposes only, as the package will only work on Windows.

### From PyPI

```sh
pip3 install clickpy
```

### From GitHub

```sh
pip3 install git+https://github.com/donno2048/clickpy
```

## Usage

Here's the method listing for the package.

 - `get_cursor_pos`: Can be used to determine the position to feed `click_at` or `clicks_at`.

Example usage:

```py
from clickpy import get_cursor_pos
get_cursor_pos()
```

 - `click_here`: The method will create a click at the current location

Example usage:

```py
from clickpy import click_here
click_here()
```

 - `click_at`: The method will create a click at the specified (x,y) coordinates

Example usage:

```py
from clickpy import click_at
click_at((0,0))
```

- `clicks_here`: The method will create a certain amount of click at the current location
The method has a number of optional keyword arguments:
   * `ms_delay` - the delay in milliseconds between the clicks [default: at fast as the OS allows]
   * `total_clicks` - the total clicks to be sent [default: infinitely many]
   * `key_stop` - a virtual key code that when entered in the keyboard the clicks will stop at once - e.g. `ord('a'.upper())` to stop on `a` key press [default: stop only after `total_clicks` clicks]
   * `key_start` - similar to `key_stop` but for starting the clicks [default: start immediately]
   * `stop_modifier` - the modifier (e.g. `ALT`, `CONTROL`, `SHIFT` and `WIN`) for `key_stop`
   * `start_modifier` - the modifier for `key_start`

Example usage:

```py
from clickpy import clicks_here, SHIFT, ALT
# will start clicking at the cursor's position one million times with 10ms delay in between when 0 is pressed and stop upon SHIFT+ALT+0
clicks_here(ms_delay=10, total_clicks=1_000_000, key_stop=ord('0'), key_start=ord('0'), stop_modifier=SHIFT|ALT)
```

 - `clicks_at`: The method will create a certain amount of clicks at the specified location
The method expects the same (optional) keyword arguments as `clicks_here` but also a (x,y) coordinates tuple which can be provided as a positional argument or as the `position` keyword

Example usage:

```py
from clickpy import clicks_at, get_cursor_pos, SHIFT, ALT
# same as the clicks_here example but at the initial position of the cursor
clicks_at(get_cursor_pos(), ms_delay=10, total_clicks=1_000_000, key_stop=ord('0'), key_start=ord('0'), stop_modifier=SHIFT|ALT)
```