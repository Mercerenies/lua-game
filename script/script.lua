
MyObject = Object:define()

local obj = MyObject:new()

function obj:draw()
  Canvas.set_color(Color(1, 0, 0))
  Canvas.draw_primitive(Constant.TRIANGLES, {
    Vector2(250, 250),
    Vector2(500, 500),
    Vector2(500, 250)
  })
end

table.insert(Room.get_objects(), obj)

--[[
print(Vector2(1, 2))
print(Vector2(1, 1) + Vector2(1, 1))
print(Vector2(1, 1) - Vector2(2, 2))
print(Vector2(1, 1) * Vector2(1, 1))
print(Vector2(1, 1) / 2)
print(Vector2(1, 1) * 2)
print(2 * Vector2(1, 1))
print(- Vector2(1, 1))
print(Vector2(1, 1) == Vector2(1, 1))
print(Vector2(1, 1).x)
print(Vector2(1, 1).y)
print(Vector2(1, 1).gibberish)
--]]
