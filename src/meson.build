# Programas del proyecto

sources = [
	'instruments/instrument.cpp',
	'instruments/instrument_dumb.cpp',
	'instruments/seno.cpp',
	'instruments/sinfm1.cpp',
	'instruments/campana.cpp',
	'instruments/woodwind.cpp',
	'instruments/genericins.cpp',
	'instruments/fagot.cpp',
	'instruments/kick.cpp',
	'instruments/guitar.cpp',
	'instruments/snare.cpp',
	'synth/envelope_adsr.cpp',
	'synth/midi_score.cpp',
	'synth/multinote_instr.cpp',
	'synth/orchest.cpp',
	'synth/synthesizer.cpp',
	'effects/effect.cpp',
	'effects/tremolo.cpp',
	'effects/vibrato.cpp',
	'effects/chorus.cpp',
	'effects/superdistor.cpp',
]

executable(
    'synth',
    sources: sources,
    include_directories: inc,
    link_args: ['-lm', '-lsndfile'],
    link_with: lib_pav,
    install: true,
)
