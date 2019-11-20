
math.randomseed(os.time())

MyObject = Object:define()

function MyObject:draw()
  local radius = 100
  Canvas.set_color(Color(1, 0, 0))
  Canvas.draw_primitive(Constant.TRIANGLES, {
    self.center,
    self.center + Vector2(radius * math.cos(self.angle), radius * math.sin(self.angle)),
    self.center + Vector2(radius * math.cos(self.angle + 0.1), radius * math.sin(self.angle + 0.1))
  })
end

function MyObject:init(t)
  self.angle = t.angle
  self.center = Window.get_size() / 2
end

function MyObject:step()
  self.angle = self.angle - 0.1
end

function MyObject:key_event(k)
  if k == Key.LEFT then
    self.center = self.center + Vector2(-2, 0)
  elseif k == Key.RIGHT then
    self.center = self.center + Vector2(2, 0)
  elseif k == Key.UP then
    self.center = self.center + Vector2(0, -2)
  elseif k == Key.DOWN then
    self.center = self.center + Vector2(0, 2)
  end
end

local angle = math.random() * 2 * math.pi
for i=1,4 do
  local obj = MyObject:new { angle = angle + i * math.pi / 2 }
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
