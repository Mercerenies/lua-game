
math.randomseed(os.time())

-- TODO I'll move this to C soon and it'll be an official part of the
-- API. But for now, we're just gonna hack it together here for
-- testing. (////)
local tmp = {}

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
  -- TODO It would be nice if we could make this indexing a bit safer.
  -- Right now, there's no actual guarantee that these userdata are
  -- consistent with __eq. (/////)
  if tmp[Key.LEFT] then
    self.center = self.center + Vector2(-2, 0)
  elseif tmp[Key.RIGHT] then
    self.center = self.center + Vector2(2, 0)
  elseif tmp[Key.UP] then
    self.center = self.center + Vector2(0, -2)
  elseif tmp[Key.DOWN] then
    self.center = self.center + Vector2(0, 2)
  end
end

function MyObject:key_down(k)
  tmp[k] = true
end

function MyObject:key_up(k)
  tmp[k] = false
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
