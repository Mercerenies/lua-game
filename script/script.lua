
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
  local moving = false
  local dir = Vector2(0, 0)
  if Keyboard.is_down(Key.LEFT) then
    dir = dir + Vector2(-1, 0)
    moving = true
  end
  if Keyboard.is_down(Key.RIGHT) then
    dir = dir + Vector2(1, 0)
    moving = true
  end
  if Keyboard.is_down(Key.UP) then
    dir = dir + Vector2(0, -1)
    moving = true
  end
  if Keyboard.is_down(Key.DOWN) then
    dir = dir + Vector2(0, 1)
    moving = true
  end
  dir = math.atan2(dir.y, dir.x)
  if moving then
    self.center = self.center + 2 * Vector2(math.cos(dir), math.sin(dir))
  end
end

--function MyObject:key_down(k)
--  tmp[k] = true
--end

--function MyObject:key_up(k)
--  tmp[k] = false
--end

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
