
math.randomseed(os.time())

MyObject = Object:define()

function MyObject:draw()
  local center = Window.get_size() / 2
  local radius = 100
  Canvas.set_color(Color(1, 0, 0))
  Canvas.draw_primitive(Constant.TRIANGLES, {
    center,
    center + Vector2(radius * math.cos(self.angle), radius * math.sin(self.angle)),
    center + Vector2(radius * math.cos(self.angle + 0.1), radius * math.sin(self.angle + 0.1))
  })
end

function MyObject:init()
  self.angle = math.random() * 2 * math.pi
end

function MyObject:step()
  self.angle = self.angle - 0.1
end

for i=1,4 do
  local obj = MyObject:new()
  table.insert(Room.get_objects(), obj)
end

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
