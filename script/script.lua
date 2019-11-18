
MyObject = Object:define()

local obj = MyObject:new()

function obj:draw()
  -- TBA
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
