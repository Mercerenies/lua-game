
MyObject = Object:define()

local obj = MyObject:new()
print(Object)
print(MyObject)
print(getmetatable(obj))

function test()
  print("Drawing")
end

print "Hello :)"

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
