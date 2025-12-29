SHOWCASE (https://www.youtube.com/watch?v=shfq3lXRWgg)

The idea was to simulate a flexible, worm- or snake-like creature made up of connected body segments that respond dynamically to mouse movement — creating smooth, lifelike motion without relying on a physics engine.

🌀 Each segment (a Segment class) knows its position, angle, radius, and a few helper points used to draw the body.

🧩 The Creature class manages an array of these segments, updating each one so that it follows the previous segment, producing a natural, flowing movement.

🌊 A wave function (based on cosine) modulates movement over time to give the illusion of a slithering or swimming motion.

🖥️ Everything is drawn in real time using SFML’s rendering API, with a custom convex shape connecting the body parts.
